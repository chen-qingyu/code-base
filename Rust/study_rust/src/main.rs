// loop
#[allow(dead_code)]
fn test_1() {
    let mut counter = 0;

    let result = loop {
        counter += 1;
        if counter == 233 {
            break counter * 10 + 3;
        }
    };

    println!("{result}");
}

// for in
#[allow(dead_code)]
fn test_2() {
    for (i, x) in (1..=10).rev().enumerate() {
        println!("{i}: {x}");
    }
    println!("LIFTOFF!");
}

// struct
#[derive(Debug, Clone, Copy)]
struct Rectangle {
    width: u32,
    length: u32,
}

impl Rectangle {
    fn square(size: u32) -> Rectangle {
        Rectangle {
            width: size,
            length: size,
        }
    }

    fn area(&self) -> u32 {
        self.width * self.length
    }
}

#[allow(dead_code)]
fn test_3() {
    let rect1 = Rectangle::square(5);
    let rect2 = rect1;
    println!("{:?} area: {}", rect2, rect1.area());
}

// enum
#[derive(Debug)]
#[allow(dead_code)]
enum Test {
    A,
    B(u32, u32),
    C { x: i32, y: i32 },
    D(String),
}

#[allow(dead_code)]
fn test_4() {
    let t1 = Test::A;
    let t2 = Test::B(1, 2);
    let t3 = Test::C { x: 233, y: 999 };
    let t4 = Test::D(String::from("hello"));

    println!("{t1:?}, {t2:?}, {t3:?}, {t4:?}");
}

// option
#[allow(dead_code)]
#[allow(unused_variables)]
#[allow(clippy::unnecessary_literal_unwrap)]
fn test_5() {
    let some_number = Some(5);
    let another_number = 10;
    let some_string = Some("hello");
    let absent_number: Option<i32> = None;

    println!("{}", some_number.unwrap() + another_number);
}

// if let
#[allow(dead_code)]
fn test_6() {
    let v = Some(3);

    match v {
        Some(3) => println!("three"),
        _ => println!("others"),
    }

    if let Some(3) = v {
        println!("three");
    } else {
        println!("others");
    }
}

// vec of enum
#[allow(dead_code)]
fn test_7() {
    #[derive(Debug)]
    enum Cell {
        Integer(i32),
        Decimal(f64),
        Text(String),
    }

    let v = vec![
        Cell::Integer(233),
        Cell::Decimal(1.5),
        Cell::Text("Hello".to_string()),
    ];

    for x in v {
        println!("{x:?}");
    }
}

// count map items
#[allow(dead_code)]
fn test_8() {
    let s = "hello world 233 233 233";

    let mut m = std::collections::HashMap::new();

    for x in s.split_whitespace() {
        *m.entry(x).or_insert(0) += 1; // Python: m[x] = m.get(x, 0) + 1
    }

    println!("{m:#?}");
}

// op?
#[allow(dead_code)]
fn read_from_file() -> Result<String, std::io::Error> {
    let result = std::fs::read_to_string("hello.txt")?;

    println!("do something");

    Ok(result)
}

#[allow(dead_code)]
fn test_9() {
    println!("{}", read_from_file().unwrap_or("default".to_string()));
}

// trait
#[allow(dead_code)]
fn largest<T: Ord>(list: &[T]) -> &T {
    let mut largest = &list[0];
    for x in list {
        if x > largest {
            largest = x;
        }
    }
    largest
}

#[allow(dead_code)]
fn test_10() {
    let v1 = vec![1, 3, 5, 7, 9, 2, 4, 6, 8, 0];
    println!("{}", largest(&v1));

    let v2 = vec!["hello".to_string(), "world".to_string()];
    println!("{}", largest(&v2));
}

// lifetime
#[allow(dead_code)]
fn longest<'a>(a: &'a str, b: &'a str) -> &'a str {
    if a.len() > b.len() {
        a
    } else {
        b
    }
}

#[allow(dead_code)]
fn test_11() {
    let s1 = "hello".to_string();
    let result;
    {
        let s2 = "233".to_string();
        result = longest(s1.as_str(), s2.as_str());
        println!("{result}");
    }
}

// input
#[allow(dead_code)]
fn test_12() {
    let mut input = String::new();
    match std::io::stdin().read_line(&mut input) {
        Ok(size) => println!("{size} bytes read: {}.", input.trim()),
        Err(error) => println!("error: {error}"),
    }
}

// pair getter/setter
#[allow(dead_code)]
#[derive(Copy, Clone)]
struct Pair {
    pair: (i32, i32),
}

impl Pair {
    fn key(&self) -> &i32 {
        &self.pair.0
    }

    fn value(&self) -> &i32 {
        &self.pair.1
    }

    fn value_mut(&mut self) -> &mut i32 {
        &mut self.pair.1
    }
}

#[allow(dead_code)]
fn test_13() {
    let mut p = Pair { pair: (1, 233) };
    println!("{}: {}", p.key(), p.value());
    *p.value_mut() = 999;
    println!("{}: {}", p.key(), p.value());
}

// multi-thread
#[allow(dead_code)]
fn test_14() {
    use std::thread;
    use std::time::Duration;

    // create first thread
    let handle = thread::spawn(move || {
        thread::sleep(Duration::from_secs(3));
        println!("Hello from the first thread!");
    });

    // create second thread
    let handle2 = thread::spawn(move || {
        println!("Hello from the second thread!");
    });

    // wait first thread
    handle.join().unwrap();

    // wait second thread
    handle2.join().unwrap();

    println!("Hello from the main thread!");
}

mod minigrep;
mod web_server;

mod nowcoder;

fn main() {
    // test_1();
    // test_2();
    // test_3();
    // test_4();
    // test_5();
    // test_6();
    // test_7();
    // test_8();
    // test_9();
    // test_10();
    // test_11();
    // test_12();
    // test_13();
    // test_14();

    // minigrep::run();
    // web_server::run();
}
