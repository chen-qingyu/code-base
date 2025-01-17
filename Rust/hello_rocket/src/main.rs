use rocket::http::Status;

#[macro_use]
extern crate rocket;

#[get("/")]
fn index() -> &'static str {
    "Hello Rocket!"
}

#[get("/hello/<name>?<id..>")]
fn greet(name: &str, id: Option<String>) -> String {
    format!("Hello {name}:{id:?}!")
}

#[get("/coffee")]
fn coffee() -> Status {
    Status::ImATeapot
}

#[launch]
fn rocket() -> _ {
    rocket::build().mount("/", routes![index, greet, coffee])
}
