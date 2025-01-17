from dashscope import Generation

with open('api_key.txt', 'r') as f:
    API_KEY = f.read().strip()


def main():
    try:
        loop()
    except KeyboardInterrupt:
        print("\rProgram terminated.")
        exit(0)


def loop():
    messages = [{'role': 'system', 'content': 'You are a helpful assistant.'}]
    while True:
        user_input = input("> ")
        messages.append({'role': 'user', 'content': user_input})
        result = Generation.call(model="qwen-turbo", messages=messages, result_format='message', api_key=API_KEY)
        assistant_output = result.output.choices[0]['message']
        print(f': {assistant_output['content']}\n')
        messages.append(assistant_output)


if __name__ == '__main__':
    main()
