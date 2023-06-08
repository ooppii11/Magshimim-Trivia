import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

class IncrementDecrementButton extends StatefulWidget {
  late TextEditingController controller;
  late int minValue;

  IncrementDecrementButton(
      {super.key, required this.controller, required this.minValue});

  @override
  _IncrementDecrementButton createState() =>
      _IncrementDecrementButton(controller, this.minValue);
}

class _IncrementDecrementButton extends State<IncrementDecrementButton> {
  late TextEditingController controller;
  late int minValue;

  _IncrementDecrementButton(this.controller, this.minValue);

  @override
  Widget build(BuildContext context) {
    return Row(
      children: <Widget>[
        Expanded(
          flex: 1,
          child: TextFormField(
            textAlign: TextAlign.center,
            decoration: InputDecoration(
              contentPadding: EdgeInsets.all(8.0),
              border: OutlineInputBorder(
                borderRadius: BorderRadius.circular(5.0),
              ),
            ),
            controller: controller,
            keyboardType: TextInputType.numberWithOptions(
              decimal: false,
              signed: true,
            ),
            inputFormatters: <TextInputFormatter>[
              FilteringTextInputFormatter.digitsOnly
            ],
          ),
        ),
        Container(
          height: 38.0,
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.center,
            mainAxisAlignment: MainAxisAlignment.center,
            children: <Widget>[
              Container(
                decoration: BoxDecoration(
                  border: Border(
                    bottom: BorderSide(
                      width: 0.5,
                    ),
                  ),
                ),
                child: InkWell(
                  child: Icon(
                    Icons.arrow_drop_up,
                    size: 18.0,
                  ),
                  onTap: () {
                    int currentValue = int.parse(controller.text);
                    setState(() {
                      currentValue++;
                      controller.text =
                          (currentValue).toString(); // incrementing value
                    });
                  },
                ),
              ),
              InkWell(
                child: Icon(
                  Icons.arrow_drop_down,
                  size: 18.0,
                ),
                onTap: () {
                  int currentValue = int.parse(controller.text);
                  setState(() {
                    if (currentValue > this.minValue) {
                      currentValue--;
                      controller.text = (currentValue > 0 ? currentValue : 0)
                          .toString(); // decrementing value
                    }
                  });
                },
              ),
            ],
          ),
        ),
      ],
    );
  }
}
