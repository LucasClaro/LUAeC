-- function soma (x, y)
--     return (x^2 * math.sin(y))/(1 + x)
-- end

function soma (x, y)
    return x+y
end

function fatorial (numero)
    total = 1
    for i=1, numero do
        total = total * i
    end
    return total
end

function bhaskara (a, b, c)
    return ((-b + math.sqrt(b*b - 4*a*c))/2*a), ((-b - math.sqrt(b*b - 4*a*c))/2*a)
end
