import 'package:flutter/material.dart';
import 'package:fluttertoast/fluttertoast.dart';

void errorToast(BuildContext context, String content, int sconds) {
  FToast fToast = FToast();
  fToast.init(context);
  Widget toast = Container(
    padding: const EdgeInsets.symmetric(horizontal: 24.0, vertical: 12.0),
    decoration: BoxDecoration(
      borderRadius: BorderRadius.circular(25.0),
      color: Colors.redAccent,
    ),
    child: Row(
      mainAxisSize: MainAxisSize.min,
      children: [
        Icon(Icons.error),
        SizedBox(
          width: 12.0,
        ),
        Text(content),
      ],
    ),
  );
  fToast.showToast(child: toast, toastDuration: Duration(seconds: sconds));
}
