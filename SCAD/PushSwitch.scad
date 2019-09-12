//translate([1,0,10])rotate([180,0,0])switch();
//rotate([0,-0,0])internalMechanics();
case();
casecover();
translate([0,2.5,-12])internalMechanics();

module casecover(){
  translate([0,0,40])mirror([0,0,1])intersection(){
    case();
    translate([0,5-1.8,0])cube([100,2,50],true);
  }
  translate([0,4,40])mirror([0,0,1]){
    translate([31,-4.2+1,6.5])cube([1.5,2,9.5]);
    translate([-8.5,-4.2+1,6.5])cube([1.5,2,9.5]);
    translate([7.5,-4.2+1,14.5])cube([6.5,2,1.5]);
    translate([25.5,-4.2+1,-4])cube([7,2,1]);    
  }
  translate([0,0,40])mirror([0,0,1])difference(){
    translate([0,2.6,0])rotate([90,0,0])cylinder(d=8,h=2,center=true,$fn=40);
    rotate([90,0,0])cylinder(d=4,h=20,center=true,$fn=30);
  }
}

module case(){
  difference(){
    union(){
      translate([12,3.1,6])cube([41,1.8,20],true);
      translate([32.5,0,0])rotate([90,0,0])cylinder(d=6,h=8,$fn=20,center=true);
      translate([-8.5,0,0])rotate([90,0,0])cylinder(d=6,h=8,$fn=20,center=true);

      translate([29,0,-3])cube([7,8,2],true);
      translate([-7,0,6])cube([3,8,20],true);
      translate([31,0,6])cube([3,8,20],true);
      translate([8.5,0,12])cube([2,8,8],true);
      translate([14,0,15])cube([12,8,2],true);
      difference(){
        translate([13,0,14])rotate([0,-21,0])cube([10,8,3],true);
        translate([13,0,18])cube([14,9,4],true);
      }
      
      translate([0,2.6,0])rotate([90,0,0])cylinder(d=8,h=2,center=true,$fn=40);
    }
    translate([32.5,0,0])rotate([90,0,0])cylinder(d=2.5,h=9,$fn=20,center=true);
    translate([-8.5,0,0])rotate([90,0,0])cylinder(d=2.5,h=9,$fn=20,center=true);
    rotate([90,0,0])cylinder(d=4,h=20,center=true,$fn=30);
    
    translate([11,0,19])rotate([0,-21,0])cylinder(d=2,h=20,center=true,$fn=10); // hole for spring
    translate([1,0,10])cube([13.5,6.5,7.5],true);
    translate([0,-5+1.8,0])cube([100,2,50],true); // remove top to have space for cover
    
    // lock holes
    translate([31,-4.2+1,6])cube([1.5,2,10]);
    translate([-8.5,-4.2+1,6])cube([1.5,2,10]);
    translate([7.5,-4.2+1,14.5])cube([7,2,2]);
    translate([25.5,-4.2+1,-5])cube([7,2,2]);    
  }
}

module internalMechanics(){
  color("White")translate([0,1.5,-3])rotate([90,-0,0])linear_extrude(3){
    difference(){
      union(){
        difference(){
          translate([0,3])circle(d=50,$fn=100);
          translate([0,23])square([80,40],true);
          translate([-20,0])square([40,40],true);
          rotate([0,0,-30])translate([0,-20])square([80,40],true);
        }
        translate([0,3])circle(d=9,$fn=40);
        translate([25,3])square([8,4],true);
        translate([17,3])square([2,5],true);
      }
      translate([0,3])circle(d=4.2,$fn=20);
    }
  }
}

module switch(){
  color([0.2,0.2,0.2])cube([13,6,7],true);
  color("Red")translate([-2,0,4])cube([1,1,1],true);
  color("LightGray")translate([0,0,5.2])rotate([0,-15,0]){cube([13,4,0.1],true);translate([8,0,0])rotate([90,0,0])cylinder(d=3,h=4,$fn=10, center=true);}
  color("LightGray"){
    translate([0,0,-4])cube([1,1,3],true);
    translate([5,0,-4])cube([1,1,3],true);
    translate([-5,0,-4])cube([1,1,3],true);
  }
  
}