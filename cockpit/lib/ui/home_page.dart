import 'dart:async';

import 'package:cockpit/ui/player_page.dart';
import 'package:flutter/material.dart';

class HomePage extends StatefulWidget {
  HomePage({Key key}) : super(key: key);

  _HomePageState createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  double _opacity = 0.3;
  @override
  void initState() {
    super.initState();

    Timer.periodic(Duration(seconds: 2), (timer) {
      print(_opacity);
      setState(() {
        _opacity == 1.0 ? _opacity = 0.3 : _opacity = 1.0;
      });
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Stack(
        children: <Widget>[
          Container(
            decoration: BoxDecoration(
              image: DecorationImage(
                  image: AssetImage("assets/images/war_backgroud.jpg"),
                  fit: BoxFit.cover),
            ),
          ),
          Container(
            padding: EdgeInsets.only(top: 20),
            alignment: Alignment.topCenter,
            child: Text(
              "Battle Field",
              style: TextStyle(
                  fontFamily: "Halo3", fontSize: 66, color: Colors.white),
            ),
          ),
          Container(
            alignment: Alignment.center,
            padding: EdgeInsets.only(top: 80),
            child: AnimatedOpacity(
              duration: Duration(seconds: 1),
              opacity: _opacity,
              child: InkWell(
                onTap: () {
                  print('start...');
                  Navigator.push(
                      context,
                      PageRouteBuilder(
                        transitionsBuilder: (
                          BuildContext context,
                          Animation<double> animation,
                          Animation<double> secondaryAnimation,
                          Widget child,
                        ) {
                          return FadeTransition(
                            opacity: animation,
                            child: child,
                          );
                        },
                        pageBuilder: (BuildContext context, Animation animation,
                            Animation secondaryAnimation) {
                          return PlayerPage();
                        },
                      ));
                },
                child: Material(
                  type: MaterialType.transparency,
                  child: Text(
                    "Start",
                    style: TextStyle(
                        fontFamily: "Headliner",
                        fontSize: 40,
                        letterSpacing: 5,
                        color: Colors.white),
                  ),
                ),
              ),
            ),
          ),
          Positioned(
            top: 8,
            right: 20,
            child: IconButton(
              onPressed: () {},
              icon: Icon(
                Icons.settings,
                color: Colors.white,
              ),
            ),
          ),
          Container(
            alignment: Alignment.bottomCenter,
            padding: EdgeInsets.only(bottom: 5),
            child: Text("Liangdi @ 蘑菇云脑洞大赛",
                style: TextStyle(
                    color: Colors.white, fontFamily: "Halo3", fontSize: 10)),
          )
        ],
      ),
    );
  }
}
