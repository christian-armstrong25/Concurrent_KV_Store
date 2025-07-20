# Distributed Key-Value Store (KVStore)

A high-performance, distributed key-value store system implemented in C++20 with support for both concurrent and distributed architectures. This project demonstrates advanced systems programming concepts including multi-threading, network programming, and distributed systems design.

## 🏗️ Architecture Overview

The KVStore system consists of three main components:

### 1. **Shardmaster** - Configuration Management

- Manages the distributed system configuration
- Handles server join/leave operations
- Manages shard distribution across servers
- Provides configuration queries

### 2. **Server** - Data Storage

- **Concurrent Mode**: Single-server with multi-threaded operations
- **Distributed Mode**: Part of a distributed cluster with shard-based data distribution
- Supports both simple and concurrent key-value store implementations
- Handles client requests via network communication

### 3. **Client** - Interface

- **Simple Client**: Direct connection to a single server
- **ShardKV Client**: Distributed client that routes requests through the shardmaster
- Interactive REPL (Read-Eval-Print Loop) for testing and debugging

## 🚀 Features

### Core Operations

- **GET**: Retrieve values by key
- **PUT**: Store key-value pairs
- **DELETE**: Remove key-value pairs
- **APPEND**: Append data to existing values
- **MULTIGET**: Batch retrieve multiple values
- **MULTIPUT**: Batch store multiple key-value pairs
- **GDPR DELETE**: Special deletion for compliance requirements

### Advanced Features

- **Concurrent Operations**: Thread-safe operations with configurable worker threads
- **Distributed Architecture**: Automatic sharding and load balancing
- **Network Communication**: TCP-based client-server communication
- **Interactive REPL**: Command-line interface for testing
- **Comprehensive Testing**: Sequential, parallel, and integration tests

## 📋 Prerequisites

- **C++20 compatible compiler** (Clang++ or G++)
- **Make** build system
- **POSIX-compliant system** (Linux, macOS)

### Compiler Requirements

```bash
# Check if you have the required compilers
clang++ --version
g++ --version
```

## 🔨 Building the Project

### 1. Navigate to the build directory

```bash
cd build
```

### 2. Build all components

```bash
make all
```

This will compile:

- `server` - The key-value store server
- `client` - The distributed client
- `simple_client` - The simple single-server client
- `shardmaster` - The configuration management server

### 3. Build specific components

```bash
# Build only the server
make server

# Build only the client
make client

# Build only the shardmaster
make shardmaster
```

### 4. Clean build artifacts

```bash
make clean
```

### 5. Format code

```bash
make format
```

## 🧪 Running Tests

### Run all tests

```bash
make check
```

### Run specific test categories

```bash
# Sequential tests
make check kvstore_sequential_tests

# Parallel tests
make check kvstore_parallel_tests

# Queue tests
make check queue_tests
```

### Run individual tests

```bash
# Example: Run a specific test
./test_put_get_delete
```

## 🎯 Usage Examples

### 1. Concurrent Mode (Single Server)

#### Start the server

```bash
# Start server on port 8080 with 4 worker threads
./server 8080 4
```

#### Connect with simple client

```bash
# Connect to the server
./simple_client localhost:8080
```

#### Use the REPL

```
> put mykey myvalue
> get mykey
myvalue
> append mykey _additional
> get mykey
myvalue_additional
> delete mykey
myvalue_additional
> quit
```

### 2. Distributed Mode (Multiple Servers)

#### Start the shardmaster

```bash
# Start shardmaster on port 5000
./shardmaster 5000
```

#### Start multiple servers

```bash
# Terminal 1: Server 1 on port 8081
./server 8081 localhost:5000 4

# Terminal 2: Server 2 on port 8082
./server 8082 localhost:5000 4

# Terminal 3: Server 3 on port 8083
./server 8083 localhost:5000 4
```

#### Connect with distributed client

```bash
# Connect to the shardmaster
./client localhost:5000
```

#### Use shardmaster commands

```
> join localhost:8081
> join localhost:8082
> join localhost:8083
> query
Configuration:
  Server: localhost:8081, Shards: [0-32767]
  Server: localhost:8082, Shards: [32768-65535]
  Server: localhost:8083, Shards: []
```

#### Use key-value operations

```
> put user:1 "John Doe"
> put user:2 "Jane Smith"
> multiget user:1 user:2
["John Doe", "Jane Smith"]
> gdpr_delete user:1
```

## 📚 API Reference

### Key-Value Operations

#### GET

```cpp
GetRequest req{.key = "mykey"};
GetResponse res;
bool success = store->Get(&req, &res);
// res.value contains the retrieved value
```

#### PUT

```cpp
PutRequest req{.key = "mykey", .value = "myvalue"};
PutResponse res;
bool success = store->Put(&req, &res);
```

#### DELETE

```cpp
DeleteRequest req{.key = "mykey"};
DeleteResponse res;
bool success = store->Delete(&req, &res);
// res.value contains the deleted value
```

#### APPEND

```cpp
AppendRequest req{.key = "mykey", .value = "_suffix"};
AppendResponse res;
bool success = store->Append(&req, &res);
```

#### MULTIGET

```cpp
MultiGetRequest req{.keys = {"key1", "key2", "key3"}};
MultiGetResponse res;
bool success = store->MultiGet(&req, &res);
// res.values contains the retrieved values
```

#### MULTIPUT

```cpp
MultiPutRequest req{
    .keys = {"key1", "key2"},
    .values = {"value1", "value2"}
};
MultiPutResponse res;
bool success = store->MultiPut(&req, &res);
```

### Shardmaster Operations

#### JOIN

```cpp
JoinRequest req{.server = "localhost:8081"};
JoinResponse res;
bool success = shardmaster->Join(&req, &res);
```

#### LEAVE

```cpp
LeaveRequest req{.server = "localhost:8081"};
LeaveResponse res;
bool success = shardmaster->Leave(&req, &res);
```

#### MOVE

```cpp
MoveRequest req{
    .server = "localhost:8081",
    .shards = {Shard{0, 1000}}
};
MoveResponse res;
bool success = shardmaster->Move(&req, &res);
```

#### QUERY

```cpp
QueryRequest req{};
QueryResponse res;
bool success = shardmaster->Query(&req, &res);
// res.config contains the current configuration
```

## 🏛️ Project Structure

```
kvstore/
├── cmd/                    # Main executables
│   ├── client.cpp         # Client entry point
│   ├── server.cpp         # Server entry point
│   └── shardmaster.cpp    # Shardmaster entry point
├── client/                # Client implementation
│   ├── simple_client.hpp  # Simple client interface
│   ├── shardkv_client.hpp # Distributed client interface
│   └── *command.cpp       # Command implementations
├── server/                # Server implementation
│   ├── server.hpp         # Server interface
│   └── synchronized_queue.cpp # Thread-safe queue
├── kvstore/               # Key-value store implementations
│   ├── kvstore.hpp        # Abstract interface
│   ├── simple_kvstore.hpp # Simple implementation
│   └── concurrent_kvstore.hpp # Thread-safe implementation
├── shardmaster/           # Shardmaster implementation
│   ├── shardmaster.hpp    # Abstract interface
│   └── static_shardmaster.hpp # Static configuration
├── net/                   # Network communication
│   ├── network_conn.cpp   # Connection handling
│   ├── network_messages.cpp # Message serialization
│   └── *commands.hpp      # Request/response structures
├── common/                # Shared utilities
│   ├── config.hpp         # Configuration structures
│   ├── shard.hpp          # Shard definitions
│   └── utils.cpp          # Utility functions
├── repl/                  # Interactive REPL
├── tests/                 # Test suites
│   ├── kvstore_sequential_tests/
│   ├── kvstore_parallel_tests/
│   └── queue_tests/
└── build/                 # Build artifacts and Makefile
```

## 🔧 Configuration

### Server Configuration

- **Port**: Network port for client connections
- **Worker Threads**: Number of concurrent worker threads (default: 4)
- **Shardmaster Address**: Required for distributed mode

### Client Configuration

- **Server Address**: For simple client (hostname:port)
- **Shardmaster Address**: For distributed client (hostname:port)

### Shardmaster Configuration

- **Port**: Network port for server connections
- **Static Configuration**: Pre-defined shard distribution

## 🐛 Debugging

### Enable Sanitizers

```bash
# Address Sanitizer
make ASAN=1

# Thread Sanitizer
make TSAN=1
```

### Server Debug Commands

```
> print store    # Display current key-value store contents
> print config   # Display current configuration
```

### Client Debug Commands

```
> get <key>      # Retrieve value
> put <key> <value>  # Store value
> delete <key>   # Delete key-value pair
> append <key> <value>  # Append to existing value
> multiget <key1> <key2> ...  # Batch retrieve
> multiput <key1> <value1> <key2> <value2> ...  # Batch store
> gdpr_delete <key>  # GDPR-compliant deletion
```

## 📊 Performance

The system is designed for high performance with:

- **Concurrent Operations**: Multi-threaded request handling
- **Efficient Serialization**: Binary message format
- **Connection Pooling**: Reusable network connections
- **Batch Operations**: MultiGet/MultiPut for efficiency

## 🤝 Contributing

1. Follow the existing code style (Google C++ Style Guide)
2. Add tests for new features
3. Update documentation as needed
4. Use `make format` before submitting changes

## 📄 License

This project is part of a CS30 distributed systems course implementation.

## 🆘 Troubleshooting

### Common Issues

1. **Port already in use**

   ```bash
   # Find and kill process using the port
   lsof -ti:8080 | xargs kill -9
   ```

2. **Compilation errors**

   ```bash
   # Clean and rebuild
   make clean
   make all
   ```

3. **Connection refused**

   - Ensure server is running before connecting client
   - Check firewall settings
   - Verify port numbers match

4. **Test failures**
   ```bash
   # Run tests with verbose output
   make check 2>&1 | tee test_output.log
   ```

For additional help, check the test output logs or run individual tests to isolate issues.
