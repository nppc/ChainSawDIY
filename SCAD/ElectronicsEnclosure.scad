$fn=40;
translate([0,-115,-20])rotate([10,0,0])cube([16,120,25],true);
translate([0,-115,-80])cube([24,120,8],true);
translate([0,-60,-55])cube([24,15,100],true);

translate([-15,70.4,-66+10])rotate([-90,0,-90])holder();
translate([0,-45,-35])rotate([90,0,0]){cylinder(d=11.5,h=6,$fn=6);cylinder(d=6,h=20);}
translate([0,-62,-35])rotate([90,0,0])cylinder(d=10.22,h=6);
//translate([-8,-45,-30])rotate([90,0,0]){cylinder(d=10.4,h=6,$fn=6);cylinder(d=5,h=20);}
translate([0,-45,-30-65])rotate([90,0,0]){cylinder(d=11.5,h=6,$fn=6);cylinder(d=6,h=20);}


color("Gray"){
difference(){
  union(){
    enclosure(0);  
    translate([8.99,-25,3.5])swProtect();
    translate([-8.99,-25,3.5])swProtect();
  }
  enclosure(1.5);
  //translate([0,0,-50])cube(100);
  translate([0.75,0,0]){
    translate([-0.75,0,0])cube([7,24,5],true); //oled hole
    translate([0,3,-3])cube([12.5,34,5],true); // place for glass
  }
  translate([0,-32,0])translate([0,0,-5])cube([13.5,20,11],true); //switch
  translate([0,-50,-18])cube([10,50,14],true); //wires hole
}
translate([7,-19,-5])cube([2,38,3.5]);
translate([-9,-19,-5])cube([3.5,38,3.5]);
}

translate([0,0,-0.5])oled();
translate([0,-32,0])switch();

module enclosure(wall){
  translate([0,-14,-8.5]){
      hull(){
      translate([0,80/2-10-wall/2,17/2-3-wall/2])cylinderRounded(20-wall,6-wall);
      translate([0,-60/2+wall/2,2.5-wall/2])cylinderRound2(20-wall*2,6-wall);
      translate([0,80/2-10-wall/2,-17/2-wall])cylinder(d=20-wall,h=1+wall);
      translate([20/2-3-wall/2,-72/2+3+wall/2,-17/2-wall])cylinder(d=6-wall,h=1+wall,$fn=30);
      translate([-20/2+3+wall/2,-72/2+3+wall/2,-17/2-wall])cylinder(d=6-wall,h=1+wall,$fn=30);
      }      
  }
}

module switch(){
    translate([0,0,-5.5])color([0.2,0.2,0.2])cube([13,19.5,11],true);
    translate([0,0,1])color([0.2,0.2,0.2])cube([15,21,2],true);
    translate([0,0,1])color("White")rotate([10,0,0])cube([10,15,5],true);

    translate([0,0,-14])color("Gray")cube([5,1,6],true);
    translate([0,-7,-14])color("Gray")cube([5,1,6],true);
    translate([0,7,-14])color("Gray")cube([5,1,6],true);
}

module oled(){
    translate([0.75,0,0]){
        translate([0,0,-0.6-1.7])color("Blue")cube([12.2,38.1,1.2],true);
        translate([0,3,-1.7/2])color([0.2,0.2,0.2])cube([11.5,33,1.7],true);
        translate([-0.75,0,0])color("DarkBlue")cube([6,23,0.2],true);
    }
}

module cylinderRounded(mdiam, rdiam){
  minkowski(){
    translate([0,0,-0.2])cylinder(d=mdiam-rdiam, h=0.2);
    sphere(d=rdiam,$fn=30);
  }
}

module cylinderRound2(mdiam, rdiam){
  rotate([0,90,0])minkowski(){
    cylinder(d=rdiam,h=mdiam-rdiam, center=true);
    sphere(d=rdiam,$fn=30);
  }
}


module swProtect(){
  hull(){
    translate([0,-13,-3])rotate([0,90,0])cylinder(d=4,h=2,center=true, $fn=20);
    rotate([0,90,0])cylinder(d=4,h=2,center=true, $fn=20);
    translate([0,-6,-6])cube([2,19,1],true);
  }
}


module holder(){
//  cylinder(d=43,h=30);
//  translate([0,-40,0])cube([100,80,30]);
//  translate([-25,-40,15])cube([40,80,15]);
difference(){
    union(){
        translate([0,-98/2,0])cube([120,98,30]);
        translate([-30,-98/2,0])cube([30,98,15]);
        //translate([105,-98/2,0])cube([15,98,36]);

        translate([5,0,15])cylinder(d=50,h=15);
    }
    translate([-1,70/2,15+15/2])rotate([0,90,0])cylinder(d=8,h=35,$fn=20);
    translate([-1,-70/2,15+15/2])rotate([0,90,0])cylinder(d=8,h=35,$fn=20);

    translate([35,-70/2,15+15/2])cube([10,13.5,16],true); // nut holder front
    translate([35,70/2,15+15/2])cube([10,13.5,16],true); // nut holder front

    //translate([95,-70/2,15+15/2])cube([10,13.5,16],true); // nut holder back
    //translate([95,70/2,15+15/2])cube([10,13.5,16],true); // nut holder back

    hull(){
      translate([75+5,0,-1])cylinder(d=50,h=40);
      translate([75-5,0,-1])cylinder(d=50,h=40);
    }
    
    translate([5,0,-1])cylinder(d=18,h=40,$fn=40); // hole for main shaft

    translate([5,0,30-10])cylinder(d=32,h=10); // bearing 15 hole
    translate([5,0,30-11])cylinder(d=26,h=12); // bearing 15 hole
    translate([5,0,0])cylinder(d=22,h=8,$fn=50); // bearing 8 hole

    // place for motor holder
    translate([75,0,-1])linear_extrude(4)hull(){
        translate([-25-10,-25])circle(d=13,$fn=40);
        translate([-25-10,25])circle(d=13,$fn=40);
        translate([25+10,-25])circle(d=13,$fn=40);
        translate([25+10,25])circle(d=13,$fn=40);
    }
    translate([75-25,-25,-1])cylinder(d=4,h=40,$fn=20);
    translate([75-25,25,-1])cylinder(d=4,h=40,$fn=20);
    translate([75+25,-25,-1])cylinder(d=4,h=40,$fn=20);
    translate([75+25,25,-1])cylinder(d=4,h=40,$fn=20);
    translate([75-25,-25,20])cylinder(d=9,h=11,$fn=30);
    translate([75-25,25,20])cylinder(d=9,h=11,$fn=30);
    translate([75+25,-25,20])cylinder(d=9,h=11,$fn=30);
    translate([75+25,25,20])cylinder(d=9,h=11,$fn=30);
    
    //place for bearing8 holder
    translate([5,0,-1])linear_extrude(2)hull(){
        translate([-12,0])circle(d=13);
        translate([12,0])circle(d=13);
        translate([0,0])circle(d=24);
    }

    //place for bearing15 holder
    translate([5,0,30-1])linear_extrude(2)hull(){
        translate([-15,0])circle(d=13);
        translate([15,0])circle(d=13);
        translate([0,0])circle(d=34);
    }

}
}