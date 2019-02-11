static void
shifttags(const Arg *arg) {
	Arg shift;
	/* wrap around tags when shifting over the ends of tagmask */
	/* only activate wrapping when the number of tags fits twice into an
	 * unsigned int */
	Bool wrap = LENGTH(tags) <= (sizeof(shift.ui) * 4) ? True : False;

	if(arg->i == 0)
		return;

	if(arg->i > 0)
		shift.ui = selmon->tagset[selmon->seltags] << arg->i;
	else {
		if(wrap) {
			shift.ui = selmon->tagset[selmon->seltags] << LENGTH(tags);
			shift.ui = shift.ui >> (-1 * arg->i);
		}
		else
			shift.ui = selmon->tagset[selmon->seltags] >> (-1 * arg->i);
	}
	if(wrap)
		shift.ui |= shift.ui >> LENGTH(tags);

	if(!(shift.ui & TAGMASK))
		return;
	view(&shift);
}
