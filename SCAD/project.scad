translate([-5,0,32])rotate([180,0,0])holder();

translate([0,0,-10])color("Gray")mainGear();
drillAdapter();
translate([0,0,5])color("LightGray")cylinder(d=8,h=46);
translate([0,0,25])ballBearing8();
//translate([0,0,25+7])ballBearing8();
translate([0,0,2])ballBearing15();

translate([0,0,33])pulley36T();

// belt length = 200mm
translate([70,0,-35])motor775();
translate([70,0,33])pulley16T();

translate([133,0,14])ushko();

module mainGear(){
  linear_extrude(10)difference(){circle(d=30);circle(d=10);}
}


module drillAdapter(){
  color("DarkGray"){cylinder(d=16,h=25);translate([0,0,-42+25])cylinder(d=10,h=42);}
}

module ballBearing8(){
  color("Gray")linear_extrude(7)difference(){circle(d=22);circle(d=8);}
}

module ballBearing15(){
  color("Gray")linear_extrude(9)difference(){circle(d=32);circle(d=15);}
}


module pulley36T(){
  color("LightGray"){cylinder(d=27.5,h=10);translate([0,0,10])cylinder(d=16,h=7);}
}

module pulley16T(){
  color("LightGray")cylinder(d=13,h=14);
}

module motor775(){
  color("Gray"){cylinder(d=42,h=67);cylinder(d=5,h=67+17);}
}

module holder(){
//  cylinder(d=43,h=30);
//  translate([0,-40,0])cube([100,80,30]);
//  translate([-25,-40,15])cube([40,80,15]);
difference(){
    union(){
        translate([0,-98/2,0])cube([120,98,30]);
        translate([-30,-98/2,0])cube([30,98,15]);
        translate([105,-98/2,0])cube([15,98,36]);

        translate([5,0,15])cylinder(d=50,h=15);
    }
    translate([-1,70/2,15+15/2])rotate([0,90,0])cylinder(d=8,h=30);
    translate([-1,-70/2,15+15/2])rotate([0,90,0])cylinder(d=8,h=30);

    translate([25,-70/2,15+15/2])cube([10,13.5,16],true); // nut holder front
    translate([25,70/2,15+15/2])cube([10,13.5,16],true); // nut holder front

    //translate([95,-70/2,15+15/2])cube([10,13.5,16],true); // nut holder back
    //translate([95,70/2,15+15/2])cube([10,13.5,16],true); // nut holder back

    hull(){
      translate([75+5,0,-1])cylinder(d=50,h=40);
      translate([75-5,0,-1])cylinder(d=50,h=40);
    }
    
    translate([5,0,-1])cylinder(d=10,h=40);

    translate([5,0,30-8])cylinder(d=32,h=10); // bearing 15 hole
    translate([5,0,-1])cylinder(d=22,h=8); // bearing 8 hole
}
}

module ushko(){
  rotate([90,0,0])difference(){
    union(){
      cylinder(d=36,h=18, center=true);
      translate([-36/4,0,0])cube([36/2,36,18],true);
    }
    cylinder(d=8,h=20, center=true);
    translate([-25-20,0,0])cube([50,50,50,],true);
  }
}