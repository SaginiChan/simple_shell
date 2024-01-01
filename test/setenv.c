int _setenv_p(const char *name, const char *value, int overwrite)
{
    char *existing_value = getenv(name), *env_var = NULL;
	int result = 0;
	size_t buffer_size = 0;

    if (existing_value != NULL && !overwrite) {
        return 0;
    }

    buffer_size = strlen(name) + strlen(value) + 2;
    env_var = (char *)malloc(buffer_size);

    if (env_var == NULL)
	{
        return -1;
    }
    snprintf(env_var, buffer_size, "%s=%s", name, value);

    result = putenv(env_var);

    if (result != 0)
	{
        free(env_var);
        return -1;
    }

    return 0;
}