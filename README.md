# FSE_Projeto_1

## Objetivos

O sistema desse projeto consiste em um gerenciador de temperaturas de um ambiente controlado. A atividade desenvolvida referente a matéria de Fundamentos de Sistemas Embarcados (2021/1).

Basicamente, o sistema consiste em dois dispositivos sendo um resistor, gerador de calor, e uma ventoinha, responsável pelo resfriamento, que atuam no controle da temperatura. Há também um sensor de temperatura que mede no ambiente controlado.

Além do que foi mostrado, as informações do sistema são a exibidos com atualização em _real-time_ pelo terminal, e interação para mudança dos parâmetros manualmente a qualquer instante, em um display LCD 16x2.

## Como executar

Clone no repositório

```bash
    git clone https://github.com/AnaCarolcs/FSE_Projeto_1
```

Entre na pasta raiz do projeto

```bash
    cd FSE_Projeto_1
```

Compile os executáveis do projeto

```bash
    make
```

Execute o projeto

```bash
    make run
```

## Experimentos

### Controle ON/OFF

Valor de histerese `3`.

![on_off.png](https://docs.google.com/spreadsheets/d/e/2PACX-1vSl_q5NdeuQx7zzj43D8lOXQEKT8P0jqnp-pyYI-rpD4423rluhdqZrvL8pRi3zFcysVpE0m3srYZmg/pubchart?oid=1160284950&format=image)

![sinal_on_off.png](https://docs.google.com/spreadsheets/d/e/2PACX-1vSl_q5NdeuQx7zzj43D8lOXQEKT8P0jqnp-pyYI-rpD4423rluhdqZrvL8pRi3zFcysVpE0m3srYZmg/pubchart?oid=120642933&format=image)

### Controle PID

Valor do KP, Ki e KD `5` `1` `5`, respectivamente.

![pid.png](https://docs.google.com/spreadsheets/d/e/2PACX-1vSl_q5NdeuQx7zzj43D8lOXQEKT8P0jqnp-pyYI-rpD4423rluhdqZrvL8pRi3zFcysVpE0m3srYZmg/pubchart?oid=1527430408&format=image)

![controle_pid.png](https://docs.google.com/spreadsheets/d/e/2PACX-1vSl_q5NdeuQx7zzj43D8lOXQEKT8P0jqnp-pyYI-rpD4423rluhdqZrvL8pRi3zFcysVpE0m3srYZmg/pubchart?oid=529823526&format=image)
