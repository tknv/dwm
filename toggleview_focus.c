static void toggleview_focus(const Arg *arg) {
	Client *c;
	toggleview(arg);
	restack(selmon);
	for(c = selmon->cl->clients; c; c = c->next) {
		if (c->tags & arg->ui && c->isfloating) {
			XRaiseWindow(dpy, c->win);
		}
	}
	for(c = selmon->cl->clients; !(c->tags & arg->ui) && c->next; c = c->next) ;
	if(c && c->tags & arg->ui)
		focus(c);
}
