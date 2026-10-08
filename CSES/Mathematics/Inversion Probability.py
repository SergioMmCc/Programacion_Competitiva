from decimal import Decimal, getcontext
 
def main():
    getcontext().prec = 70
    n = int(input())
    read = input()
    numbers = read.split()
    numbers = list(map(int, numbers))
    
    exp = [Decimal("0.0")] * 101
    se = [Decimal("0.0")] * 101
    
    ans = Decimal("0.0")
    for r in numbers:
        add = Decimal("0.0")
        for j in range(1, r+1):
            add += se[100] - se[j]
            
        ans += add / r
        
        for j in range(1, r+1):
            exp[j] += Decimal("1") / r
            
        for j in range(1, 101):
            se[j] = se[j-1] + exp[j]
            
    
    print(f"{ans:.6f}")
        
main()