use iced::widget;

#[derive(Debug, Clone, Copy)]
enum Message {
    Increment,
    Decrement,
}

#[derive(Default)]
struct Counter {
    value: i64,
}

impl Counter {
    fn update(&mut self, message: Message) {
        match message {
            Message::Increment => self.value += 1,
            Message::Decrement => self.value -= 1,
        }
    }

    fn view(&self) -> widget::Column<Message> {
        widget::column![
            widget::button("+").on_press(Message::Increment),
            widget::text(self.value),
            widget::button("-").on_press(Message::Decrement),
        ]
    }
}

pub fn main() {
    iced::run("A Cool Counter", Counter::update, Counter::view).unwrap();
}
