function drawHeart(style)

    if strcmpi(style, '2D')
        fimplicit(@(x, y) x.^2+(y-(x.^2).^(1/3)).^2-12);
        title('x^2 + (y - (x^2)^(^1^/^3^))^2 = 12');
        axis([-6, 6, -6, 6]);

    elseif strcmpi(style, '3D1')
        [x,y,z] = meshgrid(linspace(-5, 5, 120));
        f = (x.^2 + (9 * y.^2)./4 + z.^2 - 1).^3 - ((9*y.^2).*(z.^3))./80 - (x.^2).*(z.^3);
        p = patch(isosurface(x, y, z, f, 0));
        set(p, 'FaceColor', 'r');
        daspect([1 1 1]);
        view(-30, 24);

    elseif strcmpi(style, '3D2')
        f = @(x,y,z)(x.^2 + (9./4) .* y.^2 + z.^2 - 1).^3 - x.^2 .* z.^3 - (9./80) .* y.^2 .* z.^3;
        [x,y,z] = meshgrid(linspace(-3, 3));
        val = f(x, y, z);
        [p, v] = isosurface(x, y, z, val, 0);
        patch('faces', p, 'vertices', v, 'facevertexcdata',...
            jet(size(v,1)), 'facecolor', 'w', 'edgecolor', 'flat');
        view(3);
        grid on;
        axis equal;

    elseif strcmpi(style, '3D3')
        f = @(x,y,z)(x.^2 + (9./4).*y.^2 + z.^2 - 1).^3 - x.^2.*z.^3 - (9./80).*y.^2.*z.^3;
        [x, y, z] = meshgrid(linspace(-1.5, 1.5));
        val = f(x, y, z);
        isosurface(x, y, z, val, 0);
        grid on;
        axis equal;
        view(3);
        colormap([1 0.2 0.2]);

    else
        disp('arg: 2D 3D1 3D2 3D3');
    end

end