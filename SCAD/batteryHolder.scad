$fn=40;
//batteries
for(i=[-19*2:19:19*2])translate([i,0,0])rotate([90,0,0])cylinder(d=18.2,h=60,center=true,$fn=20);
    
translate([-1,0,-11])cube([103,30,2],true); // bottom
//left
translate([-50,0,-2])cube([5,20,18],true);
translate([-50,0,8])rotate([90,0,0])cylinder(d=7,h=20,center=true, $fn=30);
translate([-50,13.5,12])petlja();
translate([-50,-13.5,12])petlja();

//right
translate([49,0,-8])rotate([90,0,0])cylinder(d=7,h=30,center=true, $fn=30);

translate([49,18.5,-8])rotate([90,0,0])cylinder(d=7,h=6,center=true, $fn=30);
translate([45,18.5,15])rotate([90,0,0])cylinder(d=7,h=6,center=true, $fn=30);
translate([48,15.5,-2])rotate([0,5,0])lock();

//translate([49,-18.5,-8])rotate([90,0,0])cylinder(d=7,h=6,center=true, $fn=30);


translate([-3,0,12])cube([88,33,2],true); // top
translate([43,0,12.5])cube([10,30,3],true); // top
//translate([-3,15,13])cube([88,3,2],true); // top
hull(){
    translate([-47,-15,14])cube([1,3,3],true); // top
    translate([40.5,-15,13])cube([1,3,2],true); // top
}
hull(){
    translate([-50,-13.5,8])rotate([90,0,0],center=true)cylinder(d=7,h=3);
    translate([-47,-15,14])cube([1,3,3],true); // top
}

module petlja(){
    hull(){
        translate([0,0,-4])rotate([90,0,0])cylinder(d=7,h=6,center=true, $fn=30);
        translate([10,0,0])cube([1,6,2],true);
        translate([3,0,0])cube([1,6,2],true);
    }
}

module lock(){
    translate([-45/2,0,0])rotate([90,0,180])linear_extrude(height=6)intersection(){
        difference(){
            circle(d=45+10);
            circle(d=45);
            translate([0,6])rotate([0,0,-40])square([60,10],true);
        }
        translate([-15,6])square([30,25],true);
    }
}
