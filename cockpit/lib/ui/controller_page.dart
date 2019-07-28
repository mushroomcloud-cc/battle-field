import 'package:flutter/material.dart';

class ControllerPage extends StatefulWidget {
  ControllerPage({Key key}) : super(key: key);

  _ControllerPageState createState() => _ControllerPageState();
}

class _ControllerPageState extends State<ControllerPage> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: null,
      body: Stack(
        children: <Widget>[
          Container(
            decoration: BoxDecoration(
              image: DecorationImage(
                  image: AssetImage("assets/images/war_backgroud.jpg"),
                  fit: BoxFit.cover),
            ),
          ),
          buildFireButton(),
          buildController(),
          // buildMap()
        ],
      ),
    );
  }

  Container buildMap() {
    return Container(
          alignment: Alignment.center,
          padding: EdgeInsets.only(top: 0),
          child: Stack(
            children: <Widget>[
              Container(
                
                decoration: BoxDecoration(
                  border: Border.all(width: 2,color: Colors.white)
                ),
                width: 300,
                height: 300,
                child: Opacity(
                  opacity: 0.9,
                  child: Image.asset("assets/images/map.png",fit: BoxFit.cover,)),
              )
            ],
          ),
        );
  }

  Positioned buildController() {
    return Positioned(
          left: 10,
          bottom: 10,
          child: Stack(
            children: <Widget>[
              Container(
                width: 150,
                height: 150,
                alignment: Alignment.center,
                child: InkWell(
                  child: Image.asset("assets/images/controller_cb.png"),
                ),
              ),
              Container(
                width: 150,
                height: 150,
                alignment: Alignment.center,
                child: InkWell(
                  child: Image.asset("assets/images/controller_cs.png"),
                ),
              ),
            ],
          ),
        );
  }

  Positioned buildFireButton() {
    return Positioned(
      right: 10,
      bottom: 10,
      child: Container(
        child: InkWell(
          child: Image.asset("assets/images/fire.png"),
        ),
      ),
    );
  }
}
