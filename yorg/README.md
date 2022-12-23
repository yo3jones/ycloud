# YOrg

## Development

### Setup Development Environment

The `dev-init.sh` will do the following:

- copies the example.env to .env if it doesn't exist
- build the project using cmake
- symlink the compile_commands.json so lsp functionality will work

```shell
./scripts/dev-init.sh
```
