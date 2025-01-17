from http import HTTPStatus
import dashscope

with open('api_key.txt', 'r') as f:
    API_KEY = f.read().strip()


def call_with_prompt():
    response = dashscope.Generation.call(
        model=dashscope.Generation.Models.qwen_turbo,
        prompt='请介绍一下通义千问',
        api_key=API_KEY
    )
    if response.status_code == HTTPStatus.OK:
        print(response)
    else:
        print(response.code, response.message)


if __name__ == '__main__':
    call_with_prompt()
