$fn=20;
translate([0,0,-0.5])oled();
translate([0,-34,0])switch();

translate([0,-14,-8.5]){
    hull(){
    translate([24/2-3,80/2-3,17/2-3])sphere(d=6);
    translate([-24/2+3,80/2-3,17/2-3])sphere(d=6);
    translate([24/2-3,-80/2+3,17/2-3])sphere(d=6);
    translate([-24/2+3,-80/2+3,17/2-3])sphere(d=6);

    translate([28/2-4,100/2-4,-17/2])cylinder(d=8,h=1);
    translate([-28/2+4,100/2-4,-17/2])cylinder(d=8,h=1);
    translate([28/2-4,-90/2+4,-17/2])cylinder(d=8,h=1);
    translate([-28/2+4,-90/2+4,-17/2])cylinder(d=8,h=1);
    }
    //cube([28,80,17],true);
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