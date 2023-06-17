import 'package:flutter/material.dart';
import 'package:fluttertoast/fluttertoast.dart';

void loadingToast(BuildContext context, int sconds) {
  FToast fToast = FToast();
  fToast.init(context);
  Widget toast = Container(
    padding: const EdgeInsets.symmetric(horizontal: 24.0, vertical: 12.0),
    decoration: BoxDecoration(
      borderRadius: BorderRadius.circular(25.0),
      color: Colors.blueAccent,
    ),
    child: const Row(
      mainAxisSize: MainAxisSize.min,
      children: [
        SizedBox(
          width: 12.0,
        ),
        Text("Loading ..."),
      ],
    ),
  );
  fToast.showToast(child: toast, toastDuration: Duration(seconds: sconds));
}
