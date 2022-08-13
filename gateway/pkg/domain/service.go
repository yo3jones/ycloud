package domain

type (
	Service struct {
		ID       string         `json:"id"`
		Hostname string         `json:"hostname"`
		Routes   []ServiceRoute `json:"routes"`
	}

	ServiceRoute struct {
		PathPrefix            string `json:"pathPrefix"`
		Hostname              string `json:"hostname"`
		RequireAuthentication bool   `json:"requireAuthentication"`
		RequireAuthorization  bool   `json:"requireAuthorization"`
	}
)
