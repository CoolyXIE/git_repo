function [P, Q] = paddedsize(A, B, C, D, ~)
%�õ�����������P��Q����Сż��ֵ
%�ṩѡ��PARAM���������ͼ��
if nargin == 2
    P = 2 * A;
    Q = 2 * B;
elseif nargin == 3
    m = max(A, B);
    P = 2^nextpow2(2*m);
    Q = P;
elseif nargin == 4
    P = 2 * ceil((A + C - 1) / 2);
    Q = 2 * ceil((B + D - 1) / 2);
elseif nargin == 5
    m = max([[A B] [C D]]);
    P = 2^nextpow2(2*m);
    Q = P;
else
    error('Wrong number of inputs.')
end
