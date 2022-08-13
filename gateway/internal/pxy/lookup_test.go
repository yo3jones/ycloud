package pxy_test

import (
	"testing"

	"github.com/yo3jones/ycloud/gateway/internal/pxy"
)

type (
	testRoutePattern struct {
		pathPrefix string
	}
)

var (
	_ pxy.RoutePattern = (*testRoutePattern)(nil)
	_ pxy.RoutePattern = (*testRoutePattern)(nil)
)

func (pattern *testRoutePattern) GetPathPrefix() string {
	return pattern.pathPrefix
}

func TestIRouteLookup(t *testing.T) {
	t.Parallel()

	type test struct {
		name string
	}

	tests := []test{}

	for _, tc := range tests {
		t.Run(tc.name, func(t *testing.T) {
			t.Parallel()
		})
	}
}
