function g = intrans(f, varargin)
%
%   G = INTRANS(F, 'neg')
% 
%   G = INTRANS(F, 'log', C)
%   g = C*log(1 + F), C defaults to 1.
%   
%   G = INTRANS(F, 'gamma', GAM)
%   
%   G = INTRANS(F, 'stretch', M, E)
im = changeclass('double', f);
type = varargin{1};
if strcmp(type, 'neg')
    g = 1 - im;
elseif strcmp(type, 'log')
    C = 1
    if length(varargin)>2
        C = varargin{2}
    end
    g = C.* log( 1 + f);
elseif strcmp(type, 'gamma')
    g = imadjust(f, [], [], varargin{2});
else
    m = varargin{2};
    E = varargin{3};
    eps = 10e-6;
    g = 1./(1 + (m./(f + eps)).^E);
end
