#![allow(clippy::unused_io_amount)]

use std::{
    fs,
    io::{Read, Write},
    net, thread, time,
};

#[allow(dead_code)]
pub fn run() {
    let addr = "127.0.0.1:7878";

    let listener = net::TcpListener::bind(addr).unwrap();
    println!("Listening {}", addr);

    for stream in listener.incoming() {
        let mut stream = stream.unwrap();

        let mut buf = [0; 1024];
        stream.read(&mut buf).unwrap();
        println!("{}", String::from_utf8_lossy(&buf));

        let (status_line, filename) = if buf.starts_with(b"GET / HTTP/1.1\r\n") {
            ("HTTP/1.1 200 OK\r\n\r\n", "hello.html")
        } else if buf.starts_with(b"GET /sleep HTTP/1.1\r\n") {
            thread::sleep(time::Duration::from_secs(3));
            ("HTTP/1.1 200 OK\r\n\r\n", "hello.html")
        } else {
            ("HTTP/1.1 404 NOT FOUND\r\n\r\n", "404.html")
        };

        let contents = fs::read_to_string(filename).unwrap();
        let response = format!("{status_line}{contents}");

        stream.write(response.as_bytes()).unwrap();
        stream.flush().unwrap();
    }
}
