$fn=80;


translate([65,0,2.9])rotate([180,0,0])coverMotor(55,1.5);

//difference(){
  //projection(cut = true)
    translate([-5,0,33])rotate([180,0,0])holder();
//  cube([100,100,100]);
//}

//translate([0,0,-10])color("Gray")mainGear();
//drillAdapter();
//translate([0,0,5])color("LightGray")cylinder(d=8,h=46);
translate([0,0,24])ballBearing8();
translate([0,0,3])ballBearing15();

translate([0,0,35])pulley36T();

// belt length = 200mm
translate([75,0,-38])motor775();
translate([75,0,35])pulley20T();


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
  color("Gray")linear_extrude(7)difference(){circle(d=22,$fn=30);circle(d=8,$fn=20);}
}

module ballBearing15(){
  color("Gray")linear_extrude(9)difference(){circle(d=32,$fn=30);circle(d=15,$fn=30);}
}


module pulley36T(){
  color("LightGray"){cylinder(d=27.5,h=10,$fn=30);translate([0,0,10])cylinder(d=16,h=7,$fn=30);}
}

module pulley20T(){
  color("LightGray")cylinder(d=16,h=14, $fn=20);
}

module motor775(){
  color("Gray"){
    cylinder(d=44.5,h=67,$fn=30);
    translate([0,0,-(6+5)])cylinder(d=5,h=67+4.5+16+5+6,$fn=20);
    cylinder(d=17.5,h=67+4.5,$fn=20);
    translate([0,0,-6])cylinder(d=15,h=6,$fn=20);
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

module coverMotor(hght,wall){
  //walls
  translate([0,0,hght-10])rotate([0,0,90])cover_half_ring(10,wall);
  translate([10,0,hght-10])rotate([0,0,-90])cover_half_ring(10,wall);

  rotate([0,0,90])rotate_extrude(angle=180, convexity=10)translate([25, 0])square([wall,hght-10]);
  difference(){
    translate([10,0,0])rotate([0,0,-90])rotate_extrude(angle=180, convexity=10) translate([25, 0])square([wall,hght-10]);
    translate([10,0,38])for(i=[0:30:180])rotate([0,0,i])rotate([45,0,0])cube([100,5,5],true);
    translate([10,0,30])for(i=[15:30:180])rotate([0,0,i])rotate([45,0,0])cube([100,5,5],true);
    translate([10,0,22])for(i=[0:30:180])rotate([0,0,i])rotate([45,0,0])cube([100,5,5],true);
  }
  translate([0,-25-wall,0])cube([10,1.5,hght-10]);
  translate([0,25,0])cube([10,1.5,hght-10]);

  translate([10,15+wall,hght-10])rotate([0,-90,0])linear_extrude(height=10)cover_round(10,wall);

  translate([0,-15-wall,hght-10])rotate([0,-90,180])linear_extrude(height=10)cover_round(10,wall);
  
  //top
  translate([5,0,hght-wall]){
    linear_extrude(height=wall){
      translate([5,0,0])circle(r=16.5);
      translate([-5,0,0])circle(r=16.5);
    }
    translate([-5,-33/2,0])cube([10,33,wall]);
  }
  
  //mounting tabs
  rotate([0,0,90])translate([0,29,0])cover_mountingTab();
  translate([10,0,0]){
    rotate([0,0,-22])translate([0,29,0])cover_mountingTab();
    rotate([0,0,202])translate([0,29,0])cover_mountingTab();
  }
  
  // bottom rebro
  rotate([0,0,90])rotate_extrude(angle=180, convexity=10)translate([25,0,0])square([3,2]);
  translate([10,0,0])rotate([0,0,-90])rotate_extrude(angle=180, convexity=10)translate([25,0,0])square([3,2]);
  translate([0,25,0])cube([10,3,2]);
  translate([0,-28,0])cube([10,3,2]);
  
  // vert rebra
  translate([-26,4,0])rotate([0,0,171])cover_vertRebro(40);
  translate([-26,-4,0])rotate([0,0,189])cover_vertRebro(40);
  
  translate([10,0,0])rotate([0,0,58])translate([26,0,0])cover_vertRebro(17.5);
  translate([10,0,0])rotate([0,0,78])translate([26,0,0])cover_vertRebro(17.5);
  translate([10,0,0])rotate([0,0,282])translate([26,0,0])cover_vertRebro(17.5);
  translate([10,0,0])rotate([0,0,302])translate([26,0,0])cover_vertRebro(17.5);
  
}

module cover_vertRebro(hght){
  translate([0,-1,0])hull(){
    cube([4,2,0.1]);
    translate([0,0.5,hght])cube([0.1,1,1]);
  }
}

module cover_mountingTab(){
    linear_extrude(height=2)difference(){
      hull(){
        circle(5,$fn=40);
        translate([-15,-9,0])square([30,1]);
      }
      translate([0,1,0])circle(1.5,$fn=20);
      translate([0,-28,0])circle(25, $fn=40);
    }
}

module cover_round(r,wall){
  intersection(){
    difference(){
      circle(r,$fn=r*8); 
      circle(r-wall,$fn=r*7); 
    }
    square([r*2,r*2]);
  }
}

module cover_half_ring(r,wall)
{
 rotate_extrude(angle=180, convexity=10)
    translate([25-r+wall, 0]) 
      cover_round(r,wall);
}