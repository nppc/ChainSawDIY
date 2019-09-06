$fn=80;
//difference(){
  //projection(cut = true)
    translate([-5,0,35])rotate([180,0,0])holder();
//  cube([100,100,100]);
//}

//translate([0,0,-10])color("Gray")mainGear();
//drillAdapter();
//translate([0,0,5])color("LightGray")cylinder(d=8,h=46);
//translate([0,0,24])ballBearing8();
//translate([0,0,3])ballBearing15();

//translate([0,0,35])pulley36T();

// belt length = 200mm
//translate([70,0,-38])motor775();
//translate([70,0,35])pulley16T();


//projection(cut = false)
//translate([70,0,30])color([0.1,0.1,0.1])linear_extrude(2)motorHolder();
//translate([0,0,31])color([0.1,0.1,0.1])linear_extrude(1)bearing8holder();
//translate([0,0,2])color([0.1,0.1,0.1])linear_extrude(1)bearing15holder();


//translate([133,0,14])ushko();

module mainGear(){
  linear_extrude(10)difference(){circle(d=30);circle(d=10);}
}


module drillAdapter(){
  color("DarkGray"){cylinder(d=16,h=25);translate([0,0,-42+25])cylinder(d=10,h=42);}
}

module ballBearing8(){
  color("Gray")linear_extrude(7)difference(){circle(d=22);circle(d=8,$fn=20);}
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
  color("Gray"){
    cylinder(d=44.5,h=67);
    translate([0,0,-(6+5)])cylinder(d=5,h=67+4.5+16+5+6);
    cylinder(d=17.5,h=67+4.5);
    translate([0,0,-6])cylinder(d=15,h=6);
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


/*
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
*/


module ventHoleMotor(){
    difference(){
        hull(){
            for(i=[0:2:26])rotate([0,0,i-13])translate([29/2,0])circle(d=4,$fn=15);
        }
        circle(d=25,$fn=40);
    }
}

module motorHolder(){
    difference(){
        hull(){
            translate([-25-5,-25])circle(d=12);
            translate([-25-5,25])circle(d=12);
            translate([25+5,-25])circle(d=12);
            translate([25+5,25])circle(d=12);
        }
        rotate([0,0,45])ventHoleMotor();
        rotate([0,0,-45])ventHoleMotor();
        rotate([0,0,-45+180])ventHoleMotor();
        rotate([0,0,45-180])ventHoleMotor();

        circle(d=17.5);

        translate([29/2,0])circle(d=4);
        translate([-29/2,0])circle(d=4);

        hull(){
            translate([-25+5,-25])circle(d=4);
            translate([-25-5,-25])circle(d=4);
        }
        hull(){
            translate([-25+5,25])circle(d=4);
            translate([-25-5,25])circle(d=4);
        }

        hull(){
            translate([25+5,-25])circle(d=4);
            translate([25-5,-25])circle(d=4);
        }
        hull(){
            translate([25+5,25])circle(d=4);
            translate([25-5,25])circle(d=4);
        }
    }
}

module bearing8holder(){
    color("Black")difference(){
        hull(){
            translate([-12,0])circle(d=12);
            translate([12,0])circle(d=12);
            translate([0,0])circle(d=23);
        }
 
        circle(d=16);
        translate([-15,0])circle(d=3,$fn=10);
        translate([15,0])circle(d=3,$fn=10);
    }
}

module bearing15holder(){
    difference(){
        hull(){
            translate([-15,0])circle(d=12);
            translate([15,0])circle(d=12);
            translate([0,0])circle(d=33);
        }
 
        circle(d=21);
        translate([-18,0])circle(d=3,$fn=10);
        translate([18,0])circle(d=3,$fn=10);
    }
}