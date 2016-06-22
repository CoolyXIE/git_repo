function g = changeclass(newclass, f)
if strcmp(newclass,'uint8')==1
    g = im2uint8(f);
elseif strcmp(newclass,'uint16')==1
    g = im2uint16(f);
elseif strcmp(newclass,'double')==1
    g = im2double(f);
end

    


    