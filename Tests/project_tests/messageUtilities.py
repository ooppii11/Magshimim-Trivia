import json


MESSAGE_HEADR_SIZE = 5
INT_SIZE = 4

class message:
    def __init__(self, message_code, data):
        self.message_code = message_code
        self.message_data = json.dumps(data)
    
    @staticmethod
    def encode(message):
        data_length = len(message.message_data)
        return message.message_code.to_bytes(1, 'little') \
                + data_length.to_bytes(INT_SIZE, 'little') \
                + message.message_data.encode()


    @staticmethod
    def decode(response):
        message_code = int.from_bytes(response[0:1], 'little')
        if len(response[MESSAGE_HEADR_SIZE - 1:-1]) > 2:
            data = json.loads(response[MESSAGE_HEADR_SIZE - 1:-1].decode())
        else:
            data = {}
        return message(message_code, data)
