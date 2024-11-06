// Package docs Code generated by swaggo/swag. DO NOT EDIT
package docs

import "github.com/swaggo/swag"

const docTemplate = `{
    "schemes": {{ marshal .Schemes }},
    "swagger": "2.0",
    "info": {
        "description": "{{escape .Description}}",
        "title": "{{.Title}}",
        "contact": {},
        "version": "{{.Version}}"
    },
    "host": "{{.Host}}",
    "basePath": "{{.BasePath}}",
    "paths": {
        "/freelancer/{id}/find/projects": {
            "get": {
                "description": "Find freelancers clost to a given project",
                "consumes": [
                    "application/json"
                ],
                "produces": [
                    "application/json"
                ],
                "tags": [
                    "Search"
                ],
                "summary": "Find projects",
                "parameters": [
                    {
                        "type": "integer",
                        "description": "Freelancer Id",
                        "name": "id",
                        "in": "path",
                        "required": true
                    }
                ],
                "responses": {
                    "200": {
                        "description": "Found projects close to the input freelancer",
                        "schema": {
                            "$ref": "#/definitions/main.SearchProjectResponse"
                        }
                    },
                    "400": {
                        "description": "Freelancer ID missing in the path",
                        "schema": {
                            "$ref": "#/definitions/main.VsDefaultResponse"
                        }
                    },
                    "500": {
                        "description": "Internal server error",
                        "schema": {
                            "$ref": "#/definitions/main.VsDefaultResponse"
                        }
                    }
                }
            }
        },
        "/index/getList": {
            "get": {
                "description": "Get a list of all loaded indices",
                "consumes": [
                    "application/json"
                ],
                "produces": [
                    "application/json"
                ],
                "tags": [
                    "Index"
                ],
                "summary": "Get a list of all loadded indices",
                "responses": {
                    "200": {
                        "description": "OK",
                        "schema": {
                            "$ref": "#/definitions/main.VsIndexList"
                        }
                    },
                    "500": {
                        "description": "Internal server error",
                        "schema": {
                            "$ref": "#/definitions/main.VsDefaultResponse"
                        }
                    }
                }
            }
        },
        "/index/load": {
            "post": {
                "description": "Load index from DB to memory",
                "consumes": [
                    "application/json"
                ],
                "produces": [
                    "application/json"
                ],
                "tags": [
                    "Index"
                ],
                "summary": "Load index",
                "parameters": [
                    {
                        "description": "Default request",
                        "name": "Request",
                        "in": "body",
                        "required": true,
                        "schema": {
                            "$ref": "#/definitions/main.VsDefaultRequest"
                        }
                    }
                ],
                "responses": {
                    "200": {
                        "description": "Loaded index",
                        "schema": {
                            "$ref": "#/definitions/main.VsDefaultResponse"
                        }
                    },
                    "400": {
                        "description": "Name parameter required",
                        "schema": {
                            "$ref": "#/definitions/main.VsDefaultResponse"
                        }
                    },
                    "500": {
                        "description": "Internal server error",
                        "schema": {
                            "$ref": "#/definitions/main.VsDefaultResponse"
                        }
                    }
                }
            }
        },
        "/index/search": {
            "post": {
                "description": "Find neighbor items for a given feature vector",
                "consumes": [
                    "application/json"
                ],
                "produces": [
                    "application/json"
                ],
                "tags": [
                    "Index"
                ],
                "summary": "Find neighbor items for a given feature vector",
                "parameters": [
                    {
                        "description": "Search request",
                        "name": "Request",
                        "in": "body",
                        "required": true,
                        "schema": {
                            "$ref": "#/definitions/main.VsSearchRequest"
                        }
                    }
                ],
                "responses": {
                    "200": {
                        "description": "Found neighbors close to the input feature vector",
                        "schema": {
                            "$ref": "#/definitions/main.VsSearchResponse"
                        }
                    },
                    "400": {
                        "description": "Bad Request",
                        "schema": {
                            "$ref": "#/definitions/main.VsSearchResponse"
                        }
                    },
                    "500": {
                        "description": "Internal server error",
                        "schema": {
                            "$ref": "#/definitions/main.VsSearchResponse"
                        }
                    }
                }
            }
        },
        "/index/unload": {
            "post": {
                "description": "Unload index from memory",
                "consumes": [
                    "application/json"
                ],
                "produces": [
                    "application/json"
                ],
                "tags": [
                    "Index"
                ],
                "summary": "Unload index",
                "parameters": [
                    {
                        "description": "Default request",
                        "name": "Request",
                        "in": "body",
                        "required": true,
                        "schema": {
                            "$ref": "#/definitions/main.VsDefaultRequest"
                        }
                    }
                ],
                "responses": {
                    "200": {
                        "description": "Unloaded index",
                        "schema": {
                            "$ref": "#/definitions/main.VsDefaultResponse"
                        }
                    },
                    "400": {
                        "description": "Name parameter required",
                        "schema": {
                            "$ref": "#/definitions/main.VsDefaultResponse"
                        }
                    },
                    "500": {
                        "description": "Internal server error",
                        "schema": {
                            "$ref": "#/definitions/main.VsDefaultResponse"
                        }
                    }
                }
            }
        },
        "/par2vec": {
            "post": {
                "description": "Convert a paragraph to feature vector",
                "consumes": [
                    "application/json"
                ],
                "produces": [
                    "application/json"
                ],
                "tags": [
                    "Par2Vec"
                ],
                "summary": "Convert a paragraph to feature vector",
                "parameters": [
                    {
                        "description": "Paragraph",
                        "name": "paragraph",
                        "in": "body",
                        "required": true,
                        "schema": {
                            "$ref": "#/definitions/main.Par2VecRequest"
                        }
                    }
                ],
                "responses": {
                    "200": {
                        "description": "Successfully converted paragraph to feature vector",
                        "schema": {
                            "$ref": "#/definitions/main.Par2VecResponse"
                        }
                    },
                    "500": {
                        "description": "Internal server error",
                        "schema": {
                            "$ref": "#/definitions/main.SimpleResponse"
                        }
                    }
                }
            }
        },
        "/projects/{id}/find/freelancers": {
            "get": {
                "description": "Find freelancers clost to a given project",
                "consumes": [
                    "application/json"
                ],
                "produces": [
                    "application/json"
                ],
                "tags": [
                    "Search"
                ],
                "summary": "Find freelancers",
                "parameters": [
                    {
                        "type": "integer",
                        "description": "Project Id",
                        "name": "id",
                        "in": "path",
                        "required": true
                    }
                ],
                "responses": {
                    "200": {
                        "description": "Found freelancers close to the input project",
                        "schema": {
                            "$ref": "#/definitions/main.SearchFreelancerResponse"
                        }
                    },
                    "400": {
                        "description": "Project ID missing in the path",
                        "schema": {
                            "$ref": "#/definitions/main.VsDefaultResponse"
                        }
                    },
                    "500": {
                        "description": "Internal server error",
                        "schema": {
                            "$ref": "#/definitions/main.VsDefaultResponse"
                        }
                    }
                }
            }
        }
    },
    "definitions": {
        "main.Par2VecRequest": {
            "type": "object",
            "properties": {
                "paragraph": {
                    "type": "string"
                }
            }
        },
        "main.Par2VecResponse": {
            "type": "object",
            "properties": {
                "dim": {
                    "type": "integer"
                },
                "fvec": {
                    "type": "array",
                    "items": {
                        "type": "number"
                    }
                }
            }
        },
        "main.SearchFreelancerResponse": {
            "type": "object",
            "properties": {
                "D": {
                    "type": "array",
                    "items": {
                        "type": "number"
                    }
                },
                "message": {
                    "type": "string"
                },
                "name": {
                    "type": "array",
                    "items": {
                        "type": "string"
                    }
                },
                "numNeighbors": {
                    "type": "integer"
                },
                "numQueryVectors": {
                    "type": "integer"
                },
                "status": {
                    "type": "string"
                }
            }
        },
        "main.SearchProjectResponse": {
            "type": "object",
            "properties": {
                "D": {
                    "type": "array",
                    "items": {
                        "type": "number"
                    }
                },
                "message": {
                    "type": "string"
                },
                "name": {
                    "type": "array",
                    "items": {
                        "type": "string"
                    }
                },
                "numNeighbors": {
                    "type": "integer"
                },
                "numQueryVectors": {
                    "type": "integer"
                },
                "status": {
                    "type": "string"
                }
            }
        },
        "main.SimpleResponse": {
            "type": "object",
            "properties": {
                "message": {
                    "type": "string"
                }
            }
        },
        "main.VsDefaultRequest": {
            "type": "object",
            "properties": {
                "indexName": {
                    "type": "string"
                }
            }
        },
        "main.VsDefaultResponse": {
            "type": "object",
            "properties": {
                "message": {
                    "type": "string"
                },
                "status": {
                    "type": "string"
                }
            }
        },
        "main.VsIndexList": {
            "type": "object",
            "properties": {
                "dim": {
                    "type": "array",
                    "items": {
                        "type": "integer"
                    }
                },
                "indexName": {
                    "type": "array",
                    "items": {
                        "type": "string"
                    }
                },
                "numVectors": {
                    "type": "array",
                    "items": {
                        "type": "integer"
                    }
                }
            }
        },
        "main.VsSearchRequest": {
            "type": "object",
            "properties": {
                "dim": {
                    "type": "integer"
                },
                "indexName": {
                    "type": "string"
                },
                "numNeighbors": {
                    "type": "integer"
                },
                "numQueryVectors": {
                    "type": "integer"
                },
                "vecData": {
                    "type": "array",
                    "items": {
                        "type": "number"
                    }
                }
            }
        },
        "main.VsSearchResponse": {
            "type": "object",
            "properties": {
                "D": {
                    "type": "array",
                    "items": {
                        "type": "number"
                    }
                },
                "I": {
                    "type": "array",
                    "items": {
                        "type": "integer"
                    }
                },
                "message": {
                    "type": "string"
                },
                "numNeighbors": {
                    "type": "integer"
                },
                "numQueryVectors": {
                    "type": "integer"
                },
                "status": {
                    "type": "string"
                }
            }
        }
    }
}`

// SwaggerInfo holds exported Swagger Info so clients can modify it
var SwaggerInfo = &swag.Spec{
	Version:          "",
	Host:             "",
	BasePath:         "",
	Schemes:          []string{},
	Title:            "",
	Description:      "",
	InfoInstanceName: "swagger",
	SwaggerTemplate:  docTemplate,
	LeftDelim:        "{{",
	RightDelim:       "}}",
}

func init() {
	swag.Register(SwaggerInfo.InstanceName(), SwaggerInfo)
}
