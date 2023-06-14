import 'package:flutter/material.dart';

class CorrectPage extends StatelessWidget {
  const CorrectPage();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: SingleChildScrollView(
          scrollDirection: Axis.vertical,
          child: Center(
              child: Column(children: [
            Icon(
              Icons.check_circle_outline_outlined,
              size: 100,
              color: Colors.green,
            ),
            Text(
              "Correct answer",
              style: TextStyle(color: Colors.green, fontSize: 30),
            ),
          ]))),
    );
  }
}
