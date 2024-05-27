# Features
Support the following 4 major operation

1. Accrue Points - accrue(amount, expiry_date)
- update user balance with points tracking expiry date
- return a unique transaction_id

The accrue points action adds points to the user’s balances, with a specific expiry date. For example, an accrual request may look like accrue(1000, '2019-12-31'). This means that the user has accrued 1000 points that expire on the 31st of December 2019.
The system performing the accrual should get back, if successful, an unique transaction_id identifying the accrual.

2. Redeem points - redeem(amount)
- validate whether amount is ok
- update user balance with points tracking expiry date
- return a unique transaction_id

To redeem points, simply provide an amount to the points bank, and if there is sufficient balances, points will be deducted from the user’s account.
We will be deducting from the user’s earliest expiring points first.
Similar to the above, the system performing performing the redemption should get back an unique transaction_id identifying the deduction.

3. Refund points - refund(transaction_id, value)
- validate whether transaction_id is ok
- validate whether value is ok
- update user balance with points tracking expiry date

When refunding points, users have to provide a specific redemption transaction ID and an optional value. If the value is not provided, we will perform a full refund of all points from the original redemption. If a value is provided, we will perform a partial refund of the points redeemed.
Note that refunded points are now back in the user’s balance with the same expiry date as before. For example:
Accrual is performed for 10000 points expiring 2019-12-31
Redemption is performed for 6000 points. At this point, user has 4000 points left, expiring 2019-12-31
Partial Refund of 3000 points is done for the above redemption. Now the user has 7000 points left, expiring 2019-12-31

4. View balance
- Display overall points 
- Display points expiry in 3/6/12 months
- List Transactions sorted by date

The points bank must provide an easy way for the user to view his balances and expiry. For example, an API call to /statement would show him:
Overall non-expired points
Number of points expiring in the next 3, 6, and 12 months
List of all transactions sorted by date (e.g. Accruals, Redemptions and Refunds)

# Data 

eg. For user 1
Accrual is performed for 10000 points expiring 2019-12-31
Redemption is performed for 6000 points. At this point, user has 4000 points left, expiring 2019-12-31
Partial Refund of 3000 points is done for the above redemption. Now the user has 7000 points left, expiring 2019-12-31


1. Transaction History (static)

Transaction Date | Transaction Type | Amount | Expiry Date | Transaction ID | User ID | Success
2019-01-01 | accrue | 5000 | 2020-01-05 | NULL | 1 | T
2019-01-01 | accrue | 10000 | 2019-12-31 | NULL | 1 | T
2019-01-02 | redemption | 6000 | NULL | NULL | 1 | T
2019-01-03 | refund | 3000 | NULL | 5 | 1 | t

2. User Points table
User ID | Amount | Expiry Date | User Point ID
1 |  5000 | 2020-01-05  | 5
1 |  10000 | 2019-12-31 | 6

eg. Redeem (6000)
User ID | Amount | Expiry Date
1 | 3000  | 2020-01-05 | 5
1 | 4000 | 2019-12-31 | 6

=> Not really needed
3. Redemption (dynamic)  *****
Transaction Date | Amount | Transaction ID | User ID 
2019-01-02 | 6000 | 10 | 1 

eg. Refund (10, 3000)
2019-01-02 | 3000 | 10 | 1 

eg. Refund (10, 4000)
=> fail validation (no change)

4. Redemption Details

Transaction Date | Amount Redeemed | Transaction ID | User ID | User Point ID
2019-01-02 | 6000 | 10 | 1 | 6

eg. Refund (10, 3000)
- transaction begin 
Transaction Date | Amount Redeemed | Transaction ID | User ID | User Point ID
2019-01-02 | 6000 | 10 | 1 | 6
2019-01-02 | -6000 | 10 | 1 | 6
2019-01-02 | 3000 | 10 | 1 | 6

user point table
User ID | Amount | Expiry Date
1 | 3000  | 2020-01-05 | 5
1 | 7000 | 2019-12-31 | 6
- transaction end
- commit
