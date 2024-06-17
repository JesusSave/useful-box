module base1() {
    import("/home/qchen/Documents/Techs/arduino/esp8266/useless-box/3d1/smart-useless-box-base-v1.stl", convexity=3);
}

module base2() {
    import("/home/qchen/Documents/Techs/arduino/esp8266/useless-box/3d1/smart-useless-box-base-v2.STL", convexity=3); 
}

module esp8266() {
    import("/home/qchen/Documents/Editors/openscad/esp8266/ESP8266WemosD1mini.stl", convexity=3);
}

// Position and rotate the ESP8266 module
rotate([0, 0,90])  // Adjust the rotation angles as needed
translate([-8.2, -58, 6])  // Adjust the translation values as needed
color("red") 
esp8266();

/*
color("green") 
base1();
*/

translate([-53.5, -39.35, 0]) // Adjust values based on half of base2's dimensions
base2();