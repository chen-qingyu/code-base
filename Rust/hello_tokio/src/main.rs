use std::{
    future::Future,
    pin::Pin,
    task::{Context, Poll},
    thread,
    time::{Duration, Instant},
};

struct ReadFileFuture {}

impl Future for ReadFileFuture {
    type Output = String;

    fn poll(self: Pin<&mut Self>, _: &mut Context) -> Poll<Self::Output> {
        println!(
            "[{:?} at {:?}:{}] In ReadFileFuture poll.",
            Instant::now(),
            thread::current().id(),
            thread::current().name().unwrap()
        );
        thread::sleep(Duration::from_secs(1));
        Poll::Ready("Hello from ReadFileFuture!".to_string())
    }
}

async fn read_file() -> String {
    thread::sleep(Duration::from_secs(2));
    "Hello from read_file()!".to_string()
}

struct AsyncTimer {
    time: Instant,
}

impl AsyncTimer {
    fn new(time: Instant) -> Self {
        Self { time }
    }
}

impl Future for AsyncTimer {
    type Output = bool;

    fn poll(self: Pin<&mut Self>, _: &mut Context) -> Poll<Self::Output> {
        println!(
            "[{:?} at {:?}:{}] In AsyncTimer poll.",
            Instant::now(),
            thread::current().id(),
            thread::current().name().unwrap()
        );
        if Instant::now() < self.time {
            thread::sleep(self.time - Instant::now());
        }
        Poll::Ready(true)
    }
}

#[tokio::main]
async fn main() {
    println!(
        "[{:?} at {:?}:{}] Start!",
        Instant::now(),
        thread::current().id(),
        thread::current().name().unwrap()
    );

    let t1 = tokio::spawn(async {
        let content = read_file().await; // cannot inline, cause Instant::now() must after read_file()
        println!(
            "[{:?} at {:?}:{}] {}",
            Instant::now(),
            thread::current().id(),
            thread::current().name().unwrap(),
            content
        );
    });

    let t2 = tokio::spawn(async {
        let content = ReadFileFuture {}.await;
        println!(
            "[{:?} at {:?}:{}] {}",
            Instant::now(),
            thread::current().id(),
            thread::current().name().unwrap(),
            content
        );
    });

    let t3 = tokio::spawn(async {
        if AsyncTimer::new(Instant::now() + Duration::from_secs(3)).await {
            println!(
                "[{:?} at {:?}:{}] Now it's the time!",
                Instant::now(),
                thread::current().id(),
                thread::current().name().unwrap()
            );
        }
    });

    tokio::time::sleep(tokio::time::Duration::from_secs(4)).await;
    println!(
        "[{:?} at {:?}:{}] 4s later",
        Instant::now(),
        thread::current().id(),
        thread::current().name().unwrap()
    );

    let _ = tokio::join!(t1, t2, t3);
}
