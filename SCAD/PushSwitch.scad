translate([1,0,10])rotate([180,0,0])switch();
rotate([0,-0,0])internalMechanics();
case();

module case(){
  difference(){
    union(){
      translate([14,3,6])cube([45,2,20],true);
      translate([36.5,0,0])rotate([90,0,0])cylinder(d=6,h=8,$fn=20,center=true);
      translate([-8.5,0,0])rotate([90,0,0])cylinder(d=6,h=8,$fn=20,center=true);

      translate([33.5,0,-3])cube([6,8,2],true);
      translate([-7,0,6])cube([3,8,20],true);
      translate([35,0,6])cube([3,8,20],true);
      translate([8.5,0,12])cube([2,8,8],true);
      translate([14,0,15])cube([12,8,2],true);
      translate([11,0,13.5])rotate([0,-20,0])cube([6,8,3],true);
    }
    translate([36.5,0,0])rotate([90,0,0])cylinder(d=2.5,h=9,$fn=20,center=true);
    translate([-8.5,0,0])rotate([90,0,0])cylinder(d=2.5,h=9,$fn=20,center=true);
  }
}

module internalMechanics(){
  color("White")translate([0,1.5,-3])rotate([90,-0,0])linear_extrude(3){
    difference(){
      union(){
        difference(){
          translate([0,3])circle(d=60,$fn=60);
          translate([0,23])square([80,40],true);
          translate([-20,0])square([40,40],true);
          rotate([0,0,-25])translate([0,-20])square([80,40],true);
        }
        translate([0,3])circle(d=9,$fn=40);
        translate([29,3])square([8,4],true);
      }
      translate([0,3])circle(d=4,$fn=20);
    }
  }
}

module switch(){
  color([0.2,0.2,0.2])cube([13,6,7],true);
  color("Red")translate([-2,0,4])cube([1,1,1],true);
  color("LightGray")translate([0,0,5.2])rotate([0,-15,0]){cube([13,5,0.1],true);translate([8,0,0])rotate([90,0,0])cylinder(d=3,h=5,$fn=10, center=true);}
  color("LightGray"){
    translate([0,0,-4])cube([1,1,3],true);
    translate([5,0,-4])cube([1,1,3],true);
    translate([-5,0,-4])cube([1,1,3],true);
  }
  
}