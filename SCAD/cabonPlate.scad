projection(cut=true){
  difference(){
    translate([45-20,0,0])cube([90,30,3],true);

    translate([10,9,0])cylinder(d=2,h=6,$fn=20,center=true);
    translate([-10,9,0])cylinder(d=2,h=6,$fn=20,center=true);
    translate([10,-9,0])cylinder(d=2,h=6,$fn=20,center=true);
    translate([-10,-9,0])cylinder(d=2,h=6,$fn=20,center=true);

    translate([65,9,0])cylinder(d=2,h=6,$fn=20,center=true);
    translate([50,9,0])cylinder(d=2,h=6,$fn=20,center=true);
    translate([65,-9,0])cylinder(d=2,h=6,$fn=20,center=true);
    translate([50,-9,0])cylinder(d=2,h=6,$fn=20,center=true);

    translate([40,0,0])cylinder(d=10,h=6,$fn=50,center=true);
    translate([20,0,0])cylinder(d=10,h=6,$fn=50,center=true);

    nutHole();
    translate([60,0,0])nutHole();
  }
}

module nutHole(){
    difference(){
        cylinder(d=13,h=5,$fn=6);
        cylinder(d=6,h=15,$fn=40,center=true);
    }
}