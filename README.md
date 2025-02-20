# High-Performance C++ Web Server (Inspired by Nginx)

## Overview
This project is a **high-performance, lightweight web server** written in **C++** and inspired by **Nginx**. It efficiently handles multiple client requests using a combination of **`select()`-based event-driven I/O**, **multi-threading**, and **process forking**. The server supports static file serving, CGI execution, and HTTPS with SSL/TLS encryption.

## Features
- **Event-Driven Architecture:** Uses `select()` to monitor multiple client connections.
- **Multi-Threading & Forking:** Combines multi-threading and process forking to handle concurrent requests.
- **Asynchronous I/O:** Implements non-blocking I/O operations for enhanced performance.
- **Custom Configuration:** Reads settings from a custom configuration file.
- **Static File Serving:** Serves static files (HTML, CSS, JS, images, etc.).
- **CGI Support:** Executes dynamic content via CGI (PHP and Python).
- **HTTPS Support:** Provides SSL/TLS encryption with signature-based validation.
- **Error Logging:** Writes errors to designated log files for tracking and debugging.
- **Autoindex:** Automatically generates directory listings when an index file is absent.
- **HTTP Methods Support:** Handles `GET`, `POST`, and `DELETE` requests.
- **URL Redirection & Upload Handling:** Supports URL redirection and file uploads to specified directories.

## Installation
### Prerequisites
- Linux/macOS or another Unix-like system
- C++17 (or later) compliant compiler
- OpenSSL (for HTTPS support)
- Make (build tool)
- Siege (optional, for benchmarking)

### Clone Repository
```sh
git clone https://github.com/Poider/High-Performance-Cpp-Web-Server-Inspired-by-Nginx.git
cd High-Performance-Cpp-Web-Server-Inspired-by-Nginx
```

### Build the Server
The project uses a Makefile for building:
```sh
make
```

## Configuration
The server uses a custom configuration file (e.g., `config.confg`) to define its behavior. Below is an example configuration:

```plaintext
server 
{
    listen            localhost:3031
    server_name       server_2
    max_client_body_size  1000
    error_page 404 public/404.html
    location  / {
        allow_methods GET POST DELETE
        #redirect https://www.facebook.com/
        autoindex on
        root ./public/
        index index.aaaa
        upload_pass ./public/uploads/
        cgi_pass php ./cgi-bin/php-cgi
        cgi_pass py /usr/local/bin/python3
    }
    location /planet {
        allow_methods GET POST
        autoindex on
        root ./public/planet
        index index.html index.php
        #cgi_pass php ./cgi-bin/php-cgi
    }
    location /planet/image {
        allow_methods GET 
        autoindex on
        root ./public
        index index.php
        upload_pass ./public
        #cgi_pass php ./cgi-bin/php-cgi
    }
}

server 
{
    listen            localhost:3031
    server_name       server_1
    max_client_body_size  1000
    error_page 404 public/404.html
    location  / {
        allow_methods GET POST DELETE
        #redirect https://www.facebook.com/
        autoindex on
        root ./public/planet
        index form.html
        upload_pass ./public/uploads/
        cgi_pass php ./cgi-bin/php-cgi
        cgi_pass py /usr/local/bin/python3
    }
    location /planet {
        allow_methods GET POST
        autoindex on
        root ./public/planet
        index index.html index.php
        #cgi_pass php ./cgi-bin/php-cgi
    }
    location /planet/image {
        allow_methods GET 
        autoindex on
        root ./public
        index index.php
        upload_pass ./public
        #cgi_pass php ./cgi-bin/php-cgi
    }
}
```

## Usage
Run the web server with the configuration file specified as a command-line argument:
```sh
./HighPerformanceWebServer config.confg
```
The server will start using the settings defined in the provided configuration file. By default, it listens on the port specified in the config (e.g., `localhost:3031`).

## Benchmarking
The server has been benchmarked using **Siege**. To run a basic benchmark, execute:
```sh
siege -c 50 -t 1M http://localhost:3031/
```
Adjust the parameters as needed to simulate different loads.

## Example
After starting the server, test it by accessing the following URLs in your web browser or via tools like `curl`:
- [http://localhost:3031/](http://localhost:3031/) - Serves content from the root location.
- [http://localhost:3031/planet](http://localhost:3031/planet) - Serves content from the `/planet` location.
- [http://localhost:3031/planet/image](http://localhost:3031/planet/image) - Serves image-related content.

## Contributing
Contributions are welcome! Please open an issue or submit a pull request with improvements, bug fixes, or suggestions.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Author
Developed by [Poider](https://github.com/Poider).
