%% Persistence Toolbox Examples 

%% Barcodes to landscapes 
barcode1 = [[0,3,4,8]',[5,10,9,15]'];

barcode2 = [[0,2]',[3,5]'];
l1 = barcodeToLandscape(barcode1);
l2 = barcodeToLandscape(barcode2);


%% Compute the L^n distance between two landscapes
n = 1; 
d = landscapeDistance(l1, l2, n)

%% Compute the Bottleneck distance between two landscapes
bnd = landscapeBottleneckDistance(l1, l2)

%% Plot landscapes
figure();
plotLandscape(l1);
title('Persistent landscape 1');
figure();
plotLandscape(l2);
title('Persistent landscape 2');

%% Adding an subtracting landscapes 
sum = landscapeAdd(l1,l2);
diff = landscapeSubtract(l1,l2);
diffabs = landscapeAbsoluteValue(diff);
figure();
plotLandscape(sum);
title('Sum persistent landscape 1 & 2');
figure();
plotLandscape(diff);
title('Difference persistent landscape 1 & 2');
figure();
plotLandscape(diffabs);
title('Absolute value difference persistent landscape 1 & 2');

%% Compute the integral of a landscape 
intVal1 = landscapeIntegral(l1)
intVal2 = landscapeIntegral(l2)