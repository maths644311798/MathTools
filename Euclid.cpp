int Eulid(int a, int b)
{
	int q, x0, x1, x2, y0, y1, y2, r, r0;
	x0 = 1;
	y0 = 0;
	x2 = x1 = 0;
	y2 = y1 = 1;
	r0 = b;
	q = a / b;
	r = a - b * q;
	while (r != 0)
	{
		x2 = x0 - q * x1;
		y2 = y0 - q * y1;
		a = b;
		r0 = b = r;
		q = a / b;
		r = a - b * q;
		x0 = x1;
		x1 = x2;
		y0 = y1;
		y1 = y2;
	}
	cout << x2 << ' ' << y2 << endl;
	return r0;
}