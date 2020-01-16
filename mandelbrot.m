clc;clear;close all;
tic
n=2000;
max_iter = 50;
im = zeros(n);
px = linspace(-2,2,n);
py = linspace(-2,2,n);
[xGrid,yGrid] = meshgrid(px,py);
for k = 1:n*n
    x0 = xGrid(k);
    y0 = yGrid(k);
    x=0.0;
    y=0.0;
    iter=0;
    while (x*x+y*y<=2*2 && iter<max_iter)
        x_temp = x*x-y*y+x0;
        y= 2*x*y+y0;
        x=x_temp;
        iter = iter+1;
        im(k) = iter/max_iter;
    end
end
figure;imagesc(im);
colormap([jet();flipud(jet());0 0 0]);
axis image;
toc
%% using GPU Array
clear;
tic
n=1000;
max_iter = 50;
px = gpuArray.linspace(-2,2,n);
py = gpuArray.linspace(-2,2,n);
[xGrid,yGrid] = meshgrid(px,py);
im = zeros(n,n,'gpuArray');
z0 = complex(xGrid,yGrid);
z = z0;
for k = 0:max_iter
    z = z.*z + z0;
    inside = abs(z) <= 2;
    im = im + inside;
end
im = im/max_iter;
figure;
imagesc(px,py,im)
colormap([jet();flipud(jet());0 0 0]);
axis image;
toc