// ignore_for_file: prefer_const_constructors
import 'package:flutter/material.dart';
import 'package:trivia/Pages/signupPage.dart';
import 'package:trivia/SocketService.dart';
import 'package:trivia/Pages/ForgotPasswordPage.dart';
import 'package:trivia/Pages/HomePage.dart';
import 'package:trivia/message.dart';
import 'package:trivia/components/erroToast.dart';

// ignore: must_be_immutable
class LoginPage extends StatefulWidget {
  final SocketService socketService;

  const LoginPage({super.key, required this.socketService});

  @override
  _LoginPageState createState() => _LoginPageState(socketService);
}

class _LoginPageState extends State<LoginPage> {
  final SocketService _socketService;
  final usernameController = TextEditingController();
  final passwordController = TextEditingController();
  final ValueNotifier<bool> _showPasswordNotifier = ValueNotifier<bool>(false);

  _LoginPageState(this._socketService);

  @override
  void initState() {
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Colors.white,
      appBar: AppBar(
        title: Text("Login Page"),
      ),
      body: SingleChildScrollView(
        child: Column(
          children: <Widget>[
            Padding(
              padding: EdgeInsets.symmetric(horizontal: 15),
              child: TextField(
                controller: usernameController,
                decoration: InputDecoration(
                  labelText: 'Username',
                  hintText: 'Enter valid useranme',
                  icon: const Icon(Icons.email),
                ),
              ),
            ),
            Padding(
              padding: const EdgeInsets.only(
                left: 15.0,
                right: 15.0,
                top: 15,
                bottom: 0,
              ),
              child: TextField(
                controller: passwordController,
                obscureText: !_showPasswordNotifier.value,
                decoration: InputDecoration(
                  labelText: 'Password',
                  hintText: 'Enter secure password',
                  icon: const Icon(Icons.lock),
                  suffixIcon: IconButton(
                    icon: _showPasswordNotifier.value
                        ? const Icon(Icons.visibility)
                        : const Icon(Icons.visibility_off),
                    onPressed: () {
                      setState(() {
                        _showPasswordNotifier.value =
                            !_showPasswordNotifier.value;
                      });
                    },
                  ),
                ),
              ),
            ),
            Padding(
              padding: const EdgeInsets.only(
                left: 15.0,
                right: 15.0,
                top: 15,
                bottom: 0,
              ),
              child: Container(
                height: 50,
                width: 250,
                decoration: BoxDecoration(
                  color: Colors.blue,
                  borderRadius: BorderRadius.circular(20),
                ),
                child: TextButton(
                  onPressed: () async {
                    _socketService.sendMessage(Message(2, {
                      "username": usernameController.text,
                      "password": passwordController.text
                    }));
                    final Message receivedMessage =
                        await _socketService.receiveMessage();
                    if (receivedMessage.getCode() != 99) {
                      Navigator.pushReplacement(
                        context,
                        MaterialPageRoute(
                          builder: (_) => HomePage(
                            socketService: _socketService,
                          ),
                        ),
                      );
                    } else {
                      errorToast(context, receivedMessage.getData()["Error"], 2);
                    }
                  },
                  child: Text(
                    'Login',
                    style: TextStyle(color: Colors.white, fontSize: 25),
                  ),
                ),
              ),
            ),
            SizedBox(
              height: 130,
            ),
            TextButton(
              onPressed: () {
                Navigator.push(
                  context,
                  MaterialPageRoute(
                      builder: (_) => ForgotPasswordPage(
                            socketService: widget.socketService,
                          )),
                );
              },
              child: Text(
                'Forgot Password',
                style: TextStyle(color: Colors.blue, fontSize: 15),
              ),
            ),
            TextButton(
              onPressed: () {
                Navigator.pushReplacement(
                  context,
                  MaterialPageRoute(
                    builder: (_) => SignupPage(
                      socketService: widget.socketService,
                    ),
                  ),
                );
              },
              child: Text(
                'New User? Create Account',
                style: TextStyle(color: Colors.blue, fontSize: 15),
              ),
            ),
          ],
        ),
      ),
    );
  }
}
