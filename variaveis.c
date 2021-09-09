#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//EXEMPLOS
// ./main bhaskara 2 3 1 5 6
// ./main bhaskara 2 3 1 -5 6
// ./main fatorial 1 1 5

void f (lua_State* L, char* funcName, int nParametros, double *parametros, int tamanhoRetorno, double *retorno);
void error (lua_State* L, const char *fmt, ...);

int main(int argc, const char* argv[]) {
  lua_State* L = luaL_newstate();
  luaL_openlibs(L);

  luaL_dofile(L, "variaveis.lua");

  char nomeFunc[20];
  strcpy(nomeFunc, argv[1]);
  int tamanhoRetorno = atoi(argv[2]);
  int qtdParametros = atoi(argv[3]);

  double *parametros;
  parametros = malloc (qtdParametros * sizeof(double));

  double *retorno;
  retorno = malloc (tamanhoRetorno * sizeof(double));

  // printf("\nDigite o nome da funcao: ");
  // scanf("%s", &nomeFunc);

  // printf("\nDigite o tamanho da entrada da função: ");
  // scanf("%d", &qtdParametros);

  // printf("\nDigite o tamanho da saida da função: ");
  // scanf("%d", &tamanhoRetorno);

  // Preenche array de entrada
  int i;
  for (i = 0; i < qtdParametros; i++) {
    // double aux;
    // printf("\nDigite o %dº parâmetro: ", i);
    // scanf("%lf", &aux);
    // parametros[i] = aux;
    parametros[i] = atoi(argv[i+4]);
  }

  f(L, nomeFunc, qtdParametros, parametros, tamanhoRetorno, retorno);

  // Lê array de saida
  for (i = 0; i < tamanhoRetorno; i++) {
    printf("Valor de resultado %f\n", retorno[i]);
  } 

  lua_close(L);

  free(retorno);
  free(parametros);

  return 0;
}

void f (lua_State* L, char* funcName, int nParametros, double *parametros, int tamanhoRetorno, double *retorno) {

  /* push functions and arguments */
  lua_getglobal(L, funcName);  /* function to be called */
  int i = 0;
  for (i = 0; i < nParametros; i++)  {
    lua_pushnumber(L, parametros[i]);   /* push argument */
  }

  /* do the call (2 arguments, 1 result) */
  if (lua_pcall(L, nParametros, tamanhoRetorno, 0) != 0)
    error(L, "error running function '%s': %s\n", funcName,
              lua_tostring(L, -1));

  /* retrieve result */
  if (!lua_isnumber(L, -1))
    error(L, "function `%s' must return a number\n", funcName);

  for (i = 0; i < tamanhoRetorno; i++) {
    retorno[i] = lua_tonumber(L, -1);
    lua_pop(L, 1);
  }

}

// https://www.lua.org/pil/24.1.html#first-ex
void error (lua_State *L, const char *fmt, ...) {
  va_list argp;
  va_start(argp, fmt);
  vfprintf(stderr, fmt, argp);
  va_end(argp);
  lua_close(L);
  exit(EXIT_FAILURE);
}