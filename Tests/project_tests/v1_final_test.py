SIGNUP_TEST_MESSAGES = [{"username": "test", "password": "12345678", "email" : "XXXXXXX@XXXX.com"}, {"username": "test", "password": "123456", "email" : "XXXXXXX@XXXX.com"}]
LOGIN_TEST_MESSAGES = [{"username" : "test", "password" : "12345678"}, {"username" : "test", "password" : "123456"}]
INVAILD_MESSAGES = [{"" : ""}]

CODES = {
    "SignupRequest" : "1",
    "LoginRequest" : "2",
    "signupResponse" : "3",
    "loginResponse" : "3",
    "errorResponse" : "99",
}


def signup_test(socket):
    pass
def login_test(socket):
    pass
def error_test(socket):
    pass