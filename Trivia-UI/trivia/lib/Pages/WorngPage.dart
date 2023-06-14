import 'package:flutter/material.dart';

class WorngPage extends StatelessWidget {
  const WorngPage();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: SingleChildScrollView(
          scrollDirection: Axis.vertical,
          child: Center(
              child: Column(children: [
            Icon(
              Icons.error_outline,
              size: 150,
              color: Colors.red,
            ),
            Text(
              "Worng answer",
              style: TextStyle(color: Colors.red, fontSize: 30),
            ),
          ]))),
    );
  }
}
