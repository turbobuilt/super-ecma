# SuperECMA Language Concepts

## Introduction

SuperECMA aims to be a superset of JavaScript, retaining its familiar syntax and dynamic nature while introducing optional features for enhanced performance and control, typically found in lower-level languages. The goal is to allow developers to write standard JavaScript but "drop down" to more optimized constructs when needed for performance-critical sections.

## Core Features

### 1. Optional Static Typing

SuperECMA introduces optional type annotations for variables.

**Syntax:**

```javascript
// Standard JavaScript (still valid)
var untypedMessage = "Hello";
var count = 10;

// SuperECMA typed variables
var message: string = "Hello, typed world!";
var counter: int = 0;
var price: float = 99.99;
var data: MyCustomClass = new MyCustomClass();
```

**Purpose:**

*   **Clarity:** Improves code readability and maintainability.
*   **Safety:** Allows for compile-time or runtime type checking to catch errors early.
*   **Performance:** Enables potential optimizations by the SuperECMA runtime or compiler by knowing the data type ahead of time.
*   **Compatibility:** Code without type annotations behaves exactly like standard JavaScript.

### 2. Manual Memory Management (`wild`)

For performance-critical scenarios where garbage collection pauses are unacceptable, SuperECMA provides the `wild` keyword to opt-out of automatic memory management.

**Syntax:**

```javascript
// Standard garbage-collected object
var gcPerson = new Person("GC Bob");

// Manually managed ("wild") object
wild var wildPerson = new Person("Wild Alice");
wild var wildCounter: int = 0; // Can be used with typed variables or untyped

destroy wildPerson; // Explicitly frees memory
```

**Enhanced Reference Semantics:**

SuperECMA introduces a more flexible approach to mixing wild and GC-managed references:

```javascript
wild var x = new Person();
x.name = "Bob";

// Wild to GC reference (non-capturing)
var y = ref x;  // 'y' references 'x' but doesn't capture ownership
console.log(x.name); // "Bob" - x remains valid
console.log(y.name); // "Bob" - y is just a reference

// Later, when finished with x:
destroy x;  // Must be called by owner
console.log(y.name); // Error: "Reference to destroyed wild object"

// For explicit capturing (old behavior)
var z = capture x;  // Transfers ownership to GC
// console.log(x.name); // Error: "Wild reference has been captured"
```

**Wild Properties in GC-Managed Objects:**

GC-managed objects can contain wild properties that require explicit management:

```javascript
class ResourceManager {
  constructor() {
    // Wild property in a GC-managed object
    this.wildBuffer = wild new ArrayBuffer(1024 * 1024);
  }
  
  destroy() {
    // Must be called explicitly before object goes out of scope
    destroy this.wildBuffer;
  }
}

var manager = new ResourceManager();
// Use manager...
manager.destroy(); // Explicitly free wild resources
// manager = null; // Now GC can collect the wrapper object
```

**Wild Functions:**

Functions can be declared as `wild` to prevent GC interruptions during execution:

```javascript
// GC is suspended during this function's execution
wild function processAudioBuffer(buffer) {
  // No GC pauses during critical audio processing
  // New objects created here are GC-managed unless explicitly wild
  var result = performComplexCalculation(buffer);
  return result;
}

// Async version must be careful with suspend duration
wild async function processBatch(items) {
  // GC suspended until function completes or hits a suspend point
  for (let item of items) {
    await processItem(item); // GC resumes during await
    // When execution returns, GC is suspended again
  }
}
```

**Advanced Memory Management Semantics:**

*   **Reference Counting:** Wild objects use lightweight internal reference counting for non-owning references.

    ```javascript
    wild var original = new LargeBuffer(1000000);
    
    function process(buffer) {
      // Creates a non-owning reference, increments ref count
      var localRef = ref buffer;
      // Work with localRef...
    } // Reference automatically released when localRef goes out of scope
    
    process(original);
    // Safe to destroy when no active references exist
    destroy original;
    ```

*   **Explicit Transfer:** Ownership can be explicitly transferred between wild variables.

    ```javascript
    wild var first = new Resource();
    wild var second;
    
    // Transfer ownership (first becomes invalid)
    second = transfer first;
    
    // console.log(first); // Error: "Accessed transferred wild object"
    ```

*   **Lifetime Binding:** Wild objects can be bound to the lifetime of GC objects or scopes.

    ```javascript
    class GraphProcessor {
      constructor() {
        // Automatically destroyed when 'this' is garbage collected
        this.wildCache = wild(this) new Cache();
      }
      // No explicit destroy required
    }
    
    function processData() {
      // Automatically destroyed at end of scope
      wild(scope) var tempBuffer = new ArrayBuffer(1024 * 1024);
      
      // Use tempBuffer...
    } // tempBuffer automatically destroyed here
    ```

**Edge Cases and Solutions:**

*   **Ownership Semantics:** Wild objects follow hierarchical ownership by default.

    ```javascript
    wild var parent = new Container();
    wild var child = new Component();
    
    // Assigning to a property transfers ownership
    parent.component = child; // parent now owns child
    // child is now invalid as a standalone reference
    
    // Arrays also take ownership of wild elements
    wild var items = [];
    wild var item = new Item();
    items.push(item); // items array now owns item
    // item reference is now invalid
    
    // Later, when parent is destroyed:
    destroy parent; // Automatically destroys all owned wild objects
    ```

*   **Class Property Management:** Wild properties must be explicitly marked.

    ```javascript
    class ResourceManager {
      wild buffer; // Explicitly marked wild property
      normalRef; // Regular GC-managed property
      
      constructor() {
        this.buffer = wild new ArrayBuffer(1024);
        this.normalRef = { data: "example" };
      }
      
      updateBuffer() {
        wild var temp = wild new ArrayBuffer(2048);
        this.buffer = temp; // Ownership transfers, old buffer is destroyed
      }
    }
    ```

*   **Automatic Cleanup:** Wild variables are automatically destroyed at block end if not transferred.

    ```javascript
    function processData() {
      wild var buffer = new ArrayBuffer(1024 * 1024);
      // Use buffer...
    } // buffer automatically destroyed here
    
    // For custom cleanup actions:
    function complexOperation() {
      wild var resource = new Resource();
      
      defer { 
        // Custom cleanup code runs at block exit
        console.log("Cleaning up resource");
        resource.close();
      }
      
      // Use resource...
    } // defer block executes, then resource is destroyed
    ```

*   **The `using` Statement:** Automatically calls `.close()` on resources when execution leaves the block.

    ```javascript
    // Multi-line block with braces
    function processFile(path) {
      using (var file = new File(path)) {
        // Work with file...
        var data = file.readAll();
        processData(data);
      } // file.close() automatically called here
      
      // Single-line without braces
      using (var connection = db.connect()) connection.executeQuery("SELECT * FROM users");
      // connection.close() called immediately after the statement
      
      // Works with wild objects too
      using (wild var buffer = new LargeBuffer()) {
        // Use buffer...
      } // buffer.close() called, then the wild object is destroyed
      
      // Multiple resources
      using (var reader = new FileReader(), var writer = new FileWriter()) {
        // Both resources available in this scope
        writer.write(reader.read());
      } // writer.close() then reader.close() called in reverse declaration order
    }
    ```

*   **Interaction with Concurrency:** Thread safety mechanisms for wild objects.

    ```javascript
    wild var sharedResource = new Resource();
    
    // Lock for thread-safe access
    run async () => {
      using (await Run.lock(sharedResource)) {
        // Safe to access sharedResource here
        sharedResource.update();
      } // Lock automatically released
    }();
    ```

**Implementation Notes:**

The SuperECMA runtime handles the interaction between GC and wild objects through:

1. Fast reference counting for wild objects
2. Hierarchical ownership tracking to automate cleanup
3. Compiler-enforced safety checks for potentially dangerous operations
4. Runtime detection for "GC-free" programs that can bypass garbage collection entirely
5. Block-scoped automatic cleanup of wild variables

The design prioritizes developer safety while minimizing the need for explicit memory management through intuitive ownership semantics.

### 3. Concurrency (`run`)

SuperECMA introduces a simple way to run functions concurrently, inspired by Go's goroutines but with a JavaScript feel.

**Syntax:**

```javascript
function fetchData(url) {
  // ... performs async operation, e.g., fetch
  // Assume it returns a Promise or uses yield for async generators
  console.log(`Fetching ${url}...`);
  // yield result; // If using generators
  return fetch(url).then(res => res.json());
}

// Start concurrent operations using 'run'
var promiseA = run fetchData('/api/dataA');
var promiseB = run fetchData('/api/dataB');

// Await results individually
var resultA = await promiseA;
console.log("A:", resultA);

// Or await multiple results together
var [resultA, resultB] = await Run.all([promiseA, promiseB]);
console.log("A:", resultA, "B:", resultB);

// Parallel processing of iterables
var urls = ['/api/1', '/api/2', '/api/3'];
var results = await urls.mapParallel(url => fetchData(url), { concurrency: 2 }); // Optional concurrency limit
```

**Purpose:**

*   Simplify the creation and management of concurrent tasks for I/O-bound or CPU-bound operations.

**Atomicity and Synchronization:**

*   **Goal:** Simple operations on shared variables should ideally be atomic without requiring explicit locks from the user. The runtime should strive to ensure this where feasible (e.g., for primitive assignments).
*   **Atomic Primitives:** For guaranteed atomic read-modify-write operations, a helper is provided:
    ```javascript
    var sharedCounter: int = 0;
    // Atomically increments and returns the *previous* value
    var oldValue = Run.getAndChange(sharedCounter, (current) => current + 1);
    ```

**Challenges and Considerations:**

*   **Data Sharing:** SuperECMA makes sharing data between concurrent tasks as natural as regular JavaScript. Variables, including closures, are accessible across all concurrent tasks without any special handling.

    ```javascript
    // Shared data is directly accessible
    var counter = 0;
    var messages = [];
    
    run async () => {
      for (let i = 0; i < 10; i++) {
        counter++; // Simple operations like this are automatically atomic
        messages.push(`Task 1: ${i}`);
        await Run.sleep(10);
      }
    }();
    
    run async () => {
      for (let i = 0; i < 10; i++) {
        counter++; 
        messages.push(`Task 2: ${i}`);
        await Run.sleep(15);
      }
    }();

    // the order of message is not guaranteed, but they are both in there without problems.
    ```

*   **Built-in Atomic Operations:** For complex update operations, SuperECMA provides built-in atomic helpers:

    ```javascript
    // Safely increment a counter and get both old and new values
    var [oldValue, newValue] = Run.update(counter, (current) => current + 1);
    
    // Safely update an object property
    Run.updateAt(user, 'score', (current) => current + 10);
    
    // Compare-and-swap operation
    var success = Run.compareAndSet(status, 'pending', 'completed');
    ```

*   **Concurrent-Friendly Collections:** SuperECMA's standard collections (Array, Map, Set, etc.) are designed for concurrent usage:

    ```javascript
    // Different properties can be safely updated concurrently
    var userData = {};
    
    run async () => {
      userData.lastLogin = Date.now(); // Safe - different property
    }();
    
    run async () => {
      userData.visits = (userData.visits || 0) + 1; // Safe - different property
    }();
    
    // Maps and Sets have built-in concurrent safety for different keys
    var cache = new Map();
    
    run async () => {
      cache.set('user:123', await fetchUserData(123)); // Safe - different key
    }();
    
    run async () => {
      cache.set('user:456', await fetchUserData(456)); // Safe - different key
    }();
    ```

*   **When Mutexes Are Needed:** Explicit locking is only required for complex multi-step operations on the same data:

    ```javascript
    var inventory = { apples: 10, bananas: 5 };
    var mutex = new Run.Mutex();
    
    // Multi-step transaction requires a mutex
    async function transferItems(from, to, amount) {
      await mutex.lock();
      try {
        if (inventory[from] >= amount) {
          inventory[from] -= amount;  
          inventory[to] = (inventory[to] || 0) + amount;
          return true;
        }
        return false;
      } finally {
        mutex.unlock();
      }
    }
    
    run transferItems('apples', 'oranges', 3);
    ```

*   **`wild` Variables and Concurrency:** While SuperECMA provides automatic safety for garbage-collected variables, accessing the same `wild` variable from multiple concurrent tasks requires explicit synchronization through atomic operations or mutexes to prevent memory corruption.

## Summary

SuperECMA proposes extending JavaScript with optional typing, manual memory management, and simplified concurrency. While these features offer potential performance benefits and greater control, they also introduce significant complexity and safety challenges, particularly manual memory management (`wild`) and its interaction with the GC and concurrency. A robust implementation would require careful design of safety mechanisms, clear rules for feature interaction, and potentially significant runtime or tooling support.
