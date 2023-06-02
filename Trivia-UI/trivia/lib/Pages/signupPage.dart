import 'package:trivia/Pages/HomePage.dart';
import 'package:trivia/Pages/loginPage.dart';
import 'package:flutter/material.dart';
import 'package:trivia/SocketService.dart';
import 'package:trivia/message.dart';

// ignore: must_be_immutable
class SignupPage extends StatefulWidget {
  final SocketService socketService;

  const SignupPage({super.key, required this.socketService});

  @override
  _SignupPageState createState() => _SignupPageState(socketService);
}

class _SignupPageState extends State<SignupPage> {
  final SocketService _socketService;
  final emailController = TextEditingController();
  final usernameController = TextEditingController();
  final passwordController = TextEditingController();
  final ValueNotifier<bool> _showPasswordNotifier = ValueNotifier<bool>(false);

  _SignupPageState(this._socketService);

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Colors.white,
      appBar: AppBar(
        title: const Text("Signup page"),
      ),
      body: SingleChildScrollView(
        child: Column(
          children: <Widget>[
            Padding(
              padding: const EdgeInsets.symmetric(horizontal: 15),
              child: TextField(
                controller: usernameController,
                decoration: const InputDecoration(
                  labelText: 'Username',
                  hintText: 'Enter username',
                  icon: Icon(Icons.person),
                ),
              ),
            ),
            Padding(
              padding: const EdgeInsets.symmetric(horizontal: 15),
              child: TextField(
                controller: emailController,
                decoration: const InputDecoration(
                  labelText: 'Email',
                  hintText: 'Enter valid email id as abc@gmail.com',
                  icon: Icon(Icons.email),
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
                    borderRadius: BorderRadius.circular(20)),
                child: TextButton(
                  onPressed: () async{
                    this._socketService.sendMessage(Message(1, {
                          "username": usernameController.text,
                          "password": "passwordController.text",
                          "email": emailController.text
                        }));
                    final message = await this._socketService.receiveMessage();
                    if (message.getCode() == 0) {
                      print(message.getCode());
                      Navigator.pushReplacement(
                        context,
                        MaterialPageRoute(
                          builder: (_) => HomePage(
                            socketService: widget.socketService,
                          ),
                        ),
                      );
                    }
                  },
                  child: const Text(
                    'SginUp',
                    style: TextStyle(color: Colors.white, fontSize: 25),
                  ),
                ),
              ),
            ),
            const SizedBox(
              height: 130,
            ),
            TextButton(
              onPressed: () {
                Navigator.pushReplacement(
                  context,
                  MaterialPageRoute(
                    builder: (_) => LoginPage(
                      socketService: widget.socketService,
                    ),
                  ),
                );
              },
              child: const Text(
                'Alrady Have User? Login',
                style: TextStyle(color: Colors.blue, fontSize: 15),
              ),
            )
          ],
        ),
      ),
    );
  }
}
