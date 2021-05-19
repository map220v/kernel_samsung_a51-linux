
#include "debug-snapshot-log.h"

struct dbg_snapshot_log *p;

void remove_non_ascii(char * s, int len) {
    for (int i = 0; i < len; i++) {
        if(!s[i]) break;
        if(!(32 <= s[i] && s[i] < 127) || s[i] == '\'') s[i] = ' ';
    }
    s[len-1] = 0;
}

int main(int argc, char *argv[])
{
    FILE *f;
    int ch;
    long fsize;
    char *string;
    int i0, i1, i2;

    f = fopen(argv[1], "rb");
    if (f == NULL) {
        fputs("file read error!", stderr);
        exit(1);
    }
    fseek(f, 0, SEEK_END);
    fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  //same as rewind(f);

    string = malloc(fsize + 1);
    fread(string, fsize, 1, f);
    fclose(f);
    p = (struct dbg_snapshot_log *)string;

    printf("log = []\n");
for (i0 = 0; i0 < 8; i0++) {
for (i1 = 0; i1 < 1024; i1++) {
if (p->task[i0][i1].time == 0) break;
remove_non_ascii(p->task[i0][i1].task_comm, 16);
printf("log.append({ 'type' : 'task', 'time' : %lld.%09lld, 'cpu' : %d, 'sp' : %lu, 'pid' : %d, 'task_comm' : '%s', 'task' : '%p', })\n",
p->task[i0][i1].time/1000000000LL,p->task[i0][i1].time%1000000000LL,
i0,
p->task[i0][i1].sp,
p->task[i0][i1].pid,
p->task[i0][i1].task_comm,
p->task[i0][i1].task ? p->task[i0][i1].task :(void**)-1);
}
}
for (i0 = 0; i0 < 8; i0++) {
for (i1 = 0; i1 < 1024; i1++) {
if (p->work[i0][i1].time == 0) break;
remove_non_ascii(p->work[i0][i1].task_comm, 16);
printf("log.append({ 'type' : 'work', 'time' : %lld.%09lld, 'cpu' : %d, 'sp' : %lu, 'en' : %d, 'task_comm' : '%s', 'worker' : '%p', 'fn' : '%p', })\n",
p->work[i0][i1].time/1000000000LL,p->work[i0][i1].time%1000000000LL,
i0,
p->work[i0][i1].sp,
p->work[i0][i1].en,
p->work[i0][i1].task_comm,
p->work[i0][i1].worker ? p->work[i0][i1].worker :(void**)-1,
p->work[i0][i1].fn ? p->work[i0][i1].fn :(void**)-1);
}
}
for (i0 = 0; i0 < 8; i0++) {
for (i1 = 0; i1 < 1024; i1++) {
if (p->cpuidle[i0][i1].time == 0) break;
printf("log.append({ 'type' : 'cpuidle', 'time' : %lld.%09lld, 'cpu' : %d, 'sp' : %lu, 'modes' : '%p', 'state' : %u, 'num_online_cpus' : %u, 'delta' : %d, 'en' : %d, })\n",
p->cpuidle[i0][i1].time/1000000000LL,p->cpuidle[i0][i1].time%1000000000LL,
i0,
p->cpuidle[i0][i1].sp,
p->cpuidle[i0][i1].modes,
p->cpuidle[i0][i1].state,
p->cpuidle[i0][i1].num_online_cpus,
p->cpuidle[i0][i1].delta,
p->cpuidle[i0][i1].en);
}
}
for (i0 = 0; i0 < 4096; i0++) {
if (p->suspend[i0].time == 0) break;
remove_non_ascii(p->suspend[i0].log, 16);
printf("log.append({ 'type' : 'suspend', 'time' : %lld.%09lld, 'sp' : %lu, 'en' : %d, 'state' : %d, 'core' : %d, 'log' : '%s', 'fn' : '%p', 'dev' : '%p', })\n",
p->suspend[i0].time/1000000000LL,p->suspend[i0].time%1000000000LL,
p->suspend[i0].sp,
p->suspend[i0].en,
p->suspend[i0].state,
p->suspend[i0].core,
p->suspend[i0].log,
p->suspend[i0].fn ? p->suspend[i0].fn :(void**)-1,
p->suspend[i0].dev ? p->suspend[i0].dev :(void**)-1);
}
for (i0 = 0; i0 < 8; i0++) {
for (i1 = 0; i1 < 2048; i1++) {
if (p->irq[i0][i1].time == 0) break;
printf("log.append({ 'type' : 'irq', 'time' : %lld.%09lld, 'cpu' : %d, 'sp' : %lu, 'irq' : %d, 'latency' : %llu, 'en' : %d, 'fn' : '%p', 'desc' : '%p', })\n",
p->irq[i0][i1].time/1000000000LL,p->irq[i0][i1].time%1000000000LL,
i0,
p->irq[i0][i1].sp,
p->irq[i0][i1].irq,
p->irq[i0][i1].latency,
p->irq[i0][i1].en,
p->irq[i0][i1].fn ? p->irq[i0][i1].fn :(void**)-1,
p->irq[i0][i1].desc ? p->irq[i0][i1].desc :(void**)-1);
}
}
for (i0 = 0; i0 < 1024; i0++) {
if (p->clk[i0].time == 0) break;
printf("log.append({ 'type' : 'clk', 'time' : %lld.%09lld, 'f_name' : '%p', 'mode' : %d, 'arg' : %lu, 'clk' : '%p', })\n",
p->clk[i0].time/1000000000LL,p->clk[i0].time%1000000000LL,
p->clk[i0].f_name,
p->clk[i0].mode,
p->clk[i0].arg,
p->clk[i0].clk ? p->clk[i0].clk :(void**)-1);
}
for (i0 = 0; i0 < 1024; i0++) {
if (p->pmu[i0].time == 0) break;
printf("log.append({ 'type' : 'pmu', 'time' : %lld.%09lld, 'id' : %u, 'f_name' : '%p', 'mode' : %d, })\n",
p->pmu[i0].time/1000000000LL,p->pmu[i0].time%1000000000LL,
p->pmu[i0].id,
p->pmu[i0].f_name,
p->pmu[i0].mode);
}
for (i0 = 0; i0 < 1024; i0++) {
if (p->freq[i0].time == 0) break;
printf("log.append({ 'type' : 'freq', 'time' : %lld.%09lld, 'cpu' : %d, 'freq_type' : %d, 'freq_name' : '%p', 'old_freq' : %lu, 'target_freq' : %lu, 'en' : %d, })\n",
p->freq[i0].time/1000000000LL,p->freq[i0].time%1000000000LL,
p->freq[i0].cpu,
p->freq[i0].freq_type,
p->freq[i0].freq_name,
p->freq[i0].old_freq,
p->freq[i0].target_freq,
p->freq[i0].en);
}
for (i0 = 0; i0 < 1024; i0++) {
if (p->dm[i0].time == 0) break;
printf("log.append({ 'type' : 'dm', 'time' : %lld.%09lld, 'cpu' : %d, 'dm_num' : %d, 'min_freq' : %lu, 'max_freq' : %lu, 'wait_dmt' : %d, 'do_dmt' : %d, })\n",
p->dm[i0].time/1000000000LL,p->dm[i0].time%1000000000LL,
p->dm[i0].cpu,
p->dm[i0].dm_num,
p->dm[i0].min_freq,
p->dm[i0].max_freq,
p->dm[i0].wait_dmt,
p->dm[i0].do_dmt);
}
for (i0 = 0; i0 < 8; i0++) {
for (i1 = 0; i1 < 1024; i1++) {
if (p->hrtimers[i0][i1].time == 0) break;
printf("log.append({ 'type' : 'hrtimers', 'time' : %lld.%09lld, 'cpu' : %d, 'now' : %llu, 'en' : %d, 'timer' : '%p', 'fn' : '%p', })\n",
p->hrtimers[i0][i1].time/1000000000LL,p->hrtimers[i0][i1].time%1000000000LL,
i0,
p->hrtimers[i0][i1].now,
p->hrtimers[i0][i1].en,
p->hrtimers[i0][i1].timer ? p->hrtimers[i0][i1].timer :(void**)-1,
p->hrtimers[i0][i1].fn ? p->hrtimers[i0][i1].fn :(void**)-1);
}
}
for (i0 = 0; i0 < 1024; i0++) {
if (p->regulator[i0].time == 0) break;
remove_non_ascii(p->regulator[i0].name, 16);
printf("log.append({ 'type' : 'regulator', 'time' : %lld.%09lld, 'acpm_time' : %llu, 'cpu' : %d, 'reg' : %u, 'voltage' : %u, 'raw_volt' : %u, 'en' : %d, 'name' : '%s', })\n",
p->regulator[i0].time/1000000000LL,p->regulator[i0].time%1000000000LL,
p->regulator[i0].acpm_time,
p->regulator[i0].cpu,
p->regulator[i0].reg,
p->regulator[i0].voltage,
p->regulator[i0].raw_volt,
p->regulator[i0].en,
p->regulator[i0].name);
}
for (i0 = 0; i0 < 1024; i0++) {
if (p->thermal[i0].time == 0) break;
printf("log.append({ 'type' : 'thermal', 'time' : %lld.%09lld, 'cpu' : %d, 'temp' : %u, 'cooling_device' : '%p', 'cooling_state' : %u, 'data' : '%p', })\n",
p->thermal[i0].time/1000000000LL,p->thermal[i0].time%1000000000LL,
p->thermal[i0].cpu,
p->thermal[i0].temp,
p->thermal[i0].cooling_device,
p->thermal[i0].cooling_state,
p->thermal[i0].data ? p->thermal[i0].data :(void**)-1);
}
for (i0 = 0; i0 < 1024; i0++) {
if (p->acpm[i0].time == 0) break;
remove_non_ascii(p->acpm[i0].log, 9);
printf("log.append({ 'type' : 'acpm', 'time' : %lld.%09lld, 'acpm_time' : %llu, 'data' : %u, 'log' : '%s', })\n",
p->acpm[i0].time/1000000000LL,p->acpm[i0].time%1000000000LL,
p->acpm[i0].acpm_time,
p->acpm[i0].data,
p->acpm[i0].log);
}
for (i0 = 0; i0 < 1024; i0++) {
if (p->i2c[i0].time == 0) break;
printf("log.append({ 'type' : 'i2c', 'time' : %lld.%09lld, 'cpu' : %d, 'num' : %d, 'en' : %d, 'adp' : '%p', 'msgs' : '%p', })\n",
p->i2c[i0].time/1000000000LL,p->i2c[i0].time%1000000000LL,
p->i2c[i0].cpu,
p->i2c[i0].num,
p->i2c[i0].en,
p->i2c[i0].adp ? p->i2c[i0].adp :(void**)-1,
p->i2c[i0].msgs ? p->i2c[i0].msgs :(void**)-1);
}
for (i0 = 0; i0 < 1024; i0++) {
if (p->spi[i0].time == 0) break;
printf("log.append({ 'type' : 'spi', 'time' : %lld.%09lld, 'cpu' : %d, 'en' : %d, 'ctlr' : '%p', 'cur_msg' : '%p', })\n",
p->spi[i0].time/1000000000LL,p->spi[i0].time%1000000000LL,
p->spi[i0].cpu,
p->spi[i0].en,
p->spi[i0].ctlr ? p->spi[i0].ctlr :(void**)-1,
p->spi[i0].cur_msg ? p->spi[i0].cur_msg :(void**)-1);
}
for (i0 = 0; i0 < 8192; i0++) {
if (p->binder[i0].time == 0) break;
remove_non_ascii(p->binder[i0].base.from_pid_comm, 16);
remove_non_ascii(p->binder[i0].base.from_tid_comm, 16);
remove_non_ascii(p->binder[i0].base.to_pid_comm, 16);
remove_non_ascii(p->binder[i0].base.to_tid_comm, 16);
printf("log.append({ 'type' : 'binder', 'time' : %lld.%09lld, 'cpu' : %d, 'trace_type' : %d, 'transaction_id' : %d, 'from_pid' : %d, 'from_tid' : %d, 'to_pid' : %d, 'to_tid' : %d, 'to_node_id' : %d, 'reply' : %d, 'flags' : %u, 'code' : %u, 'return_error' : %u, 'return_error_param' : %u, 'return_error_line' : %u, 'from_pid_comm' : '%s', 'from_tid_comm' : '%s', 'to_pid_comm' : '%s', 'to_tid_comm' : '%s', })\n",
p->binder[i0].time/1000000000LL,p->binder[i0].time%1000000000LL,
p->binder[i0].cpu,
p->binder[i0].base.trace_type,
p->binder[i0].base.transaction_id,
p->binder[i0].base.from_pid,
p->binder[i0].base.from_tid,
p->binder[i0].base.to_pid,
p->binder[i0].base.to_tid,
p->binder[i0].transaction.to_node_id,
p->binder[i0].transaction.reply,
p->binder[i0].transaction.flags,
p->binder[i0].transaction.code,
p->binder[i0].error.return_error,
p->binder[i0].error.return_error_param,
p->binder[i0].error.return_error_line,
p->binder[i0].base.from_pid_comm,
p->binder[i0].base.from_tid_comm,
p->binder[i0].base.to_pid_comm,
p->binder[i0].base.to_tid_comm);
}
for (i0 = 0; i0 < 2048; i0++) {
if (p->printkl[i0].time == 0) break;
printf("log.append({ 'type' : 'printkl', 'time' : %lld.%09lld, 'cpu' : %d, 'msg' : %lu, 'val' : %lu, 'caller' :['%p', '%p', '%p', '%p',], })\n",
p->printkl[i0].time/1000000000LL,p->printkl[i0].time%1000000000LL,
p->printkl[i0].cpu,
p->printkl[i0].msg,
p->printkl[i0].val,
p->printkl[i0].caller[0] ? p->printkl[i0].caller[0] :(void**)-1,
p->printkl[i0].caller[1] ? p->printkl[i0].caller[1] :(void**)-1,
p->printkl[i0].caller[2] ? p->printkl[i0].caller[2] :(void**)-1,
p->printkl[i0].caller[3] ? p->printkl[i0].caller[3] :(void**)-1);
}
for (i0 = 0; i0 < 2048; i0++) {
if (p->printk[i0].time == 0) break;
remove_non_ascii(p->printk[i0].log, 128);
printf("log.append({ 'type' : 'printk', 'time' : %lld.%09lld, 'cpu' : %d, 'log' : '%s', 'caller' :['%p', '%p', '%p', '%p',], })\n",
p->printk[i0].time/1000000000LL,p->printk[i0].time%1000000000LL,
p->printk[i0].cpu,
p->printk[i0].log,
p->printk[i0].caller[0] ? p->printk[i0].caller[0] :(void**)-1,
p->printk[i0].caller[1] ? p->printk[i0].caller[1] :(void**)-1,
p->printk[i0].caller[2] ? p->printk[i0].caller[2] :(void**)-1,
p->printk[i0].caller[3] ? p->printk[i0].caller[3] :(void**)-1);
}

    return 0;
}

