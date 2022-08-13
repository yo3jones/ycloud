package pxy

import (
	"net/url"
)

type (
	// RouteLookup is used for efficiently looking up a back end service to
	// route to given a URL.
	RouteLookup[V any] interface {
		// Add will register a route pattern to reutrn the given value if a url
		// matches.
		Add(pattern RoutePattern, v V)

		// Get returns a value that has a matching route pattern.
		// It will also return whether a value was found or not.
		Get(u url.URL) (V, bool)

		// Remove will remove a pattern from the lookup.
		Remove(pattern RoutePattern)
	}

	// RoutePattern represents a route pattern to be.
	RoutePattern interface {
		GetPathPrefix() string
	}

	IRouteLookup[V any] struct{}
)

var (
	_ RouteLookup[any] = (*IRouteLookup[any])(nil)
	_ RouteLookup[any] = (*IRouteLookup[any])(nil)
)

func (*IRouteLookup[V]) Add(_ RoutePattern, _ V) {}

func (*IRouteLookup[V]) Get(_ url.URL) (V, bool) {
	var v V

	return v, false
}

func (*IRouteLookup[V]) Remove(_ RoutePattern) {}
