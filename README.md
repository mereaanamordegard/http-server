# http-server
A minimal HTTP/1.1 server implementation in C++ using Winsock2 API with RAII resource management.
- Listens on 127.0.0.1:8080
- Responds with 200 OK and blank "Hello World" HTML page
## build
- Requires Visual Studio(open .sln and build solution) or MinGW compiler(link with -lws2_32 in build arguments)

