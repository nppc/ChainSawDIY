//translate([1,0,10])rotate([180,0,0])switch();
//rotate([0,-0,0])internalMechanics();

rotate([-90,0,0]){ // rotate for printing
  case();
  translate([0,0,37])casecover();
  translate([0,2.5-0.3,-11])internalMechanics();
}

module casecover(){
  mirror([0,0,1])intersection(){
    case();
    translate([0,5-1.8,0])cube([100,2,50],true);
  }
  translate([0,4.2,0])mirror([0,0,1]){
    translate([31.1,-4.2+1.2,2])cube([1.4,2,8.5]);
    translate([-8.5,-4.2+1.2,1.25])cube([1.4,2,9.5]);
    translate([7.5,-4.2+1.2,14.6])cube([6.5,2,1.4]);
    translate([25.5,-4.2+1.2,-4])cube([6,2,0.9]);    
  }
  mirror([0,0,1])difference(){
    translate([0,2.6,0])rotate([90,0,0])cylinder(d=8,h=2,center=true,$fn=40);
    rotate([90,0,0])cylinder(d=3.1,h=20,center=true,$fn=30);
  }
  mirror([0,0,1])translate([21,2.6,5])rotate([0,-15,0])cube([3,2,16],true);
}

module case(){
  difference(){
    union(){
      translate([12,3.1,6]){
        hull(){
        translate([-41/2+1,0,10-1])rotate([90,0,0])cylinder(d=2,h=1.8,center=true,$fn=20);
        translate([-41/2+1,0,-10+1])rotate([90,0,0])cylinder(d=2,h=1.8,center=true,$fn=20);
        translate([41/2-1,0,10-1])rotate([90,0,0])cylinder(d=2,h=1.8,center=true,$fn=20);
        translate([41/2-1,0,-10+1])rotate([90,0,0])cylinder(d=2,h=1.8,center=true,$fn=20);
        }
        translate([-41/2+1,-2,10-1])rotate([90,0,0])cylinder(d=2,h=8,center=true,$fn=20);
        translate([-41/2+1,-2,-10+1])rotate([90,0,0])cylinder(d=2,h=8,center=true,$fn=20);
        translate([41/2-1,-2,10-1])rotate([90,0,0])cylinder(d=2,h=8,center=true,$fn=20);
        translate([41/2-1,-2,-10+1])rotate([90,0,0])cylinder(d=2,h=8,center=true,$fn=20);
      }
      translate([29,0,14])rotate([90,0,0])cylinder(d=7,h=8,$fn=40,center=true);

      translate([28.5,0,-3])cube([6,8,2],true);
      translate([-6.5,0,15])cube([2,8,2],true);
      translate([-7,0,6])cube([3,8,18],true);
      translate([31,0,6])cube([3,8,18],true);
      translate([8.5,0,12])cube([2,8,8],true);
      translate([14,0,15])cube([12,8,2],true);
      difference(){
        translate([13,0,14])rotate([0,-21,0])cube([10,8,3],true);
        translate([13,0,18])cube([14,9,4],true);
      }
      
      translate([0,2.6,0])rotate([90,0,0])cylinder(d=8,h=2,center=true,$fn=40);
      translate([21,2.6,5])rotate([0,-15,0])cube([3,2,16],true);
      difference(){
        translate([-5,0,-2])cube([5,8,4],true);
        rotate([90,0,0])cylinder(d=9.5,h=9,center=true, $fn=40);
        translate([-2,0,-3])cube([2,8,4],true);
      }
    }
    translate([29,0,14])rotate([90,0,0])cylinder(d=3.2,h=9,$fn=20,center=true);
    rotate([90,0,0])cylinder(d=3.1,h=20,center=true,$fn=30);
    
    translate([11,0,19])rotate([0,-21,0])cylinder(d=2.2,h=20,center=true,$fn=10); // hole for spring
    translate([1,0,10])cube([13,6,7],true); // place for micric
    translate([0,-5+1.8,0])cube([100,2,50],true); // remove top to have space for cover
    
    // lock holes
    translate([30.95,-4.2+1,1.75])cube([1.6,2,9]);
    translate([-8.55,-4.2+1,1])cube([1.6,2,10]);
    translate([7.5,-4.2+1,14.45])cube([7,2,2]);
    translate([25.5,-4.2+1,-4.95])cube([7,2,2]);    

    translate([0,5-0.3,0])cube([100,2,100],true);   // make case thinner

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
        translate([24.5,3])square([7,4],true);
        translate([17,3])square([2,5],true);
        translate([9,3])square([10,2],true);
      }
      translate([0,3])circle(d=3.2,$fn=20);
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