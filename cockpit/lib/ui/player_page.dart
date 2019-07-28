import 'package:cockpit/ui/controller_page.dart';
import 'package:flutter/material.dart';

class PlayerPage extends StatefulWidget {
  PlayerPage({Key key}) : super(key: key);

  _PlayerPageState createState() => _PlayerPageState();
}

class _PlayerPageState extends State<PlayerPage> {
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
              padding: EdgeInsets.only(top: 130),
              child: Row(
                
                mainAxisAlignment: MainAxisAlignment.center,
                children: <Widget>[
                  InkWell(
                    onTap: (){
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
                          return ControllerPage();
                        },
                      ));
                    },
                                      child: Container(
                      margin: EdgeInsets.all(10),
                      padding: EdgeInsets.all(10),
                      decoration: BoxDecoration(
                        color: Colors.white12,
                        border: Border.all(
                          color: Colors.white60,
                          width: 3
                        ),
                       
                      ),
                      width: 150,
                      child: Image.asset("assets/images/red.png"),
                    ),
                  ),
                  Container(
                    margin: EdgeInsets.all(10),
                    padding: EdgeInsets.all(10),
                    decoration: BoxDecoration(
                      color: Colors.white12
                    ),
                    width: 150,
                    child: Image.asset("assets/images/green.png"),
                  )
                ],
              ),
            )
         ],
       ),
    );
  }
}