use actix_web::{get, web, App, HttpRequest, HttpResponse, HttpServer, Responder};

#[get("/")]
async fn index() -> impl Responder {
    "Hello Actix!"
}

#[get("/hello/{name}")]
async fn greet(req: HttpRequest, name: web::Path<String>) -> impl Responder {
    format!("Hello {name}:{}!", req.query_string())
}

#[get("/coffee")]
async fn coffee() -> impl Responder {
    HttpResponse::ImATeapot()
}

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    HttpServer::new(|| App::new().service(index).service(greet).service(coffee))
        .bind(("127.0.0.1", 8080))?
        .run()
        .await
}
