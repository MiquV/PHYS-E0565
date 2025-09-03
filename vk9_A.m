clear all 
close all


solmu = [-20,30];
p1 = [-8,3];
p2 = [14,25];
p3 = [25,4];
kantama = 10;
maksimi = 17;
maksimi = 19;

x = [1,2;3,4;5,6];

rajoitukset(x,p1,p2,p3,kantama,maksimi)
[x,fval] = fmincon(@(x) etaisyyssumma(x, solmu),[0,0;0,0;0,0],[],[], [], [], [-20,-10;-20,-10;-20,-10],[30,30;30,30;30,30],@(x) rajoitukset(x,p1,p2,p3,kantama,maksimi))

piirragsm(x(1,1),x(1,2),x(2,1),x(2,2),x(3,1),x(3,2),'Maksimietäisyys = 19 km')



function [c, ceq] = rajoitukset(x,p1,p2,p3,kantama,maksimi)
    
    ceq = [];

    c = [etaisyys(x(1,:),x(2,:)) - maksimi;
        etaisyys(x(1,:),x(3,:)) - maksimi;
        etaisyys(x(2,:),x(3,:)) - maksimi;
        etaisyys(x(1,:),p1) - kantama;
        etaisyys(x(2,:),p2) - kantama;
        etaisyys(x(3,:),p3) - kantama];
    
end

function fval = etaisyyssumma(x, solmu)

fval = etaisyys(solmu,x(1,:)) + etaisyys(solmu,x(2,:)) + etaisyys(solmu,x(3,:));

end

function d = etaisyys(x1,x2)

d = sqrt((x2(1)-x1(1))^2+(x2(2)-x1(2))^2);

end
